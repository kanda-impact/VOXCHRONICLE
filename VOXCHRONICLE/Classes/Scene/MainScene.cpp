//
//  MainScene.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/8/28.
//
//

#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <boost/random.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>

#include "MainScene.h"
#include "Enemy.h"
#include "MapSelector.h"
#include "LuaObject.h"
#include "FileUtils.h"
#include "BlinkLayer.h"
#include "TitleScene.h"
#include "PauseLayer.h"
#include "GameOverLayer.h"
#include "Ground.h"
#include "VQString.h"
#include "MessageManager.h"
#include "BufferCache.h"
#include "EndingScene.h"
#include "SEManager.h"
#include "SaveData.h"

#include "FreePlayScene.h"

#include "CCRemoveFromParentAction.h"

using namespace std;
using namespace cocos2d;
using namespace VISS;

const int PAUSE_LAYER_TAG = 10;

// MainSceneに置いてあるモノの深度
typedef enum {
  MainSceneZOrderBackground,
  MainSceneZOrderMapBackground,
  MainSceneZOrderGround,
  MainSceneZOrderEnemyManager,
  MainSceneZOrderStatus,
  MainSceneZOrderController,
  MainSceneZOrderFocus,
  MainSceneZOrderEffect,
  MainSceneZOrderMessageWindow,
  MainSceneZOrderDamageLabel,
  MainSceneZOrderCutIn,
  MainSceneZOrderUI
} MainSceneZOrder;

bool MainScene::init() {
  LuaObject* setting = new LuaObject("Script/setting", "Setting");
  setting->autorelease();
  Map* map = new Map(setting->getString("initialMap"));
  map->autorelease();
  return this->init(map);
}

bool MainScene::init(Map* map) {
  return this->init(map, map->getInitialLevel());
}

bool MainScene::init(Map* map, int initialLevel) {
  if ( !CCLayer::init() ) {
    return false;
  }
  _isContinue = false;
  _initialLevel = initialLevel;
  SimpleAudioEngine::sharedEngine()->unloadAllEffect();
  CCTextureCache::sharedTextureCache()->removeAllTextures();
  _backScene = MainBackSceneTitle;
  Enemy::loadLifeColors();
  Music* music = new Music(3);
  music->autorelease();
  music->setTrackDidBackFunction(boost::bind(&MainScene::trackDidBack, this, _1, _2, _3));
  music->setTrackDidFinishFunction(boost::bind(&MainScene::trackDidFinishPlaying, this, _1, _2, _3, _4));
  music->setTrackWillFinishFunction(boost::bind(&MainScene::trackWillFinishPlaying, this, _1, _2, _3, _4));
  
  _skin = NULL;
  _effectLayer = EffectLayer::sharedLayer();
  _effectLayer->reloadEffects();
  
  _currentSkillInfo.skillTrackName = "";
  _currentSkillInfo.type = SkillPerformTypeNone;
  _currentSkillInfo.skill = NULL;
  
  _mapTurnCount = 0;
  
  _log = new PlayLog();
  
  CCDirector* director = CCDirector::sharedDirector();
  
  // EnemyManager
  _enemyManager = EnemyManager::create();
  _enemyManager->retain();

  _characterManager = new CharacterManager();
  CCSize size = director->getWinSize();
  _musicManager = new MusicManager(music, NULL, _enemyManager, _characterManager);
  _state = VCStateIntro;
  
  _messageWindow = new MessageWindow(FONT_NAME, 16, CCSizeMake(400, 40));
  _messageWindow->setPosition(ccp(director->getWinSize().width / 2.0f, director->getWinSize().height - 70));
  _messageWindow->setTextSpeed(4);
  _messageWindow->setLastDelay(5.0f);
  MessageManager::sharedManager()->setDefaultMessageWindow(_messageWindow);
  _effectLayer->addChild(_messageWindow, EffectLayerZOrderMessage);
  
  _mapSelector = NULL;
  
  this->scheduleUpdate();
  
  Skin* skin = map->getSkin();
  Controller* controller = new Controller(skin->getPrefix().c_str());
  controller->autorelease();
  skin->setController(controller);
  
  this->changeMap(map, initialLevel); // マップの設定
  _characterManager->setLevel(_level->getLevel()); // 初期レベル設定
  
  this->addChild(_enemyManager, MainSceneZOrderEnemyManager);
  this->addChild(_skin->getController(), MainSceneZOrderController);
  this->updateGUI();
  _skin->getController()->updateSkills(_characterManager, _level, false);
  
  _qteTrigger = NULL;
  _isLevelUped = false;
  _preLevel = _level->getLevel();
  
  CCAssert(_effectLayer != NULL, "EffectLayer must not be null.");
  CCNode* parent = _effectLayer->getParent();
  if (parent) {
    parent->removeChild(_effectLayer, true);
    _effectLayer->removeAllChildrenWithCleanup(true);
  }
  this->addChild(_effectLayer, MainSceneZOrderEffect);
  
  _effectLayer->setCharacterEffect(_characterManager->getCurrentCharacter()); // キャラクター登録
  
  this->setTouchEnabled(true);
  
  CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
  
  return true;
}

MainScene::~MainScene() {
  _enemyManager->release();
  _characterManager->release();
  if (_mapSelector != NULL) {
    _mapSelector->release();
  }
  _messageWindow->release();
  
  if (_qteTrigger != NULL) {
    _qteTrigger->release();
  }
  _skin->release();
  
  _log->release();
  
  _level->release();
  _map->release();
  _musicManager->release();
  CCLog("main scene is released");
}

void MainScene::onExit() {
  CCLayer::onExit(); // 後処理
}

void MainScene::teardown() {
  _musicManager->getMusic()->stop();
  _effectLayer->removeAllChildrenWithCleanup(true);
  MessageManager::purgeMessageManager();
  SaveData::sharedData()->save();
  EffectLayer::purgeEffectLayer();
  CCTextureCache::sharedTextureCache()->removeUnusedTextures();
  Species::purgeSpeciesCache();
  CCLuaEngine::defaultEngine()->cleanStack();
  SimpleAudioEngine::sharedEngine()->unloadAllEffect();
  CCLog("teardown");
}

void MainScene::update(float dt) {
  switch (_state) {
    case VCStateMain:
      _skin->getController()->setEnable(!_characterManager->isPerforming());
      break;
    default:
      break;
  }
}

Music* MainScene::getMusic() {
  return _musicManager->getMusic();
}

Map* MainScene::getMap() {
  return _map;
}

void MainScene::onEnterTransitionDidFinish() {
  SimpleAudioEngine::sharedEngine()->unloadAllEffect();
  _skin->getController()->setEnable(false);
  _musicManager->getMusic()->play();
  _skin->getStatusLayer()->setMarkerDuration(_musicManager->getMusic()->getTrack(0)->getDuration() / 4.0f);
  CCDictionary* dict = CCDictionary::create();
  dict->setObject(CCString::create(_characterManager->getCurrentCharacter()->getName()), "chara");
  if (_isContinue) {
    MessageManager::sharedManager()->pushRandomMessageFromFunction("continue", _map, _characterManager, _enemyManager);
    _isContinue = false;
  } else {
    MessageManager::sharedManager()->pushRandomMessageFromFunction("welcome", _map, _characterManager, _enemyManager);
  }
  _effectLayer->addWaitMarker(_musicManager->getMusic()->getCurrentMainTrack()->getDuration() * _musicManager->getMusicSet()->getIntroCount());
}

void MainScene::trackDidBack(Music *music, Track *currentTrack, int trackNumber) {
  int preTension = _characterManager->getTension(); // 敵の行動前テンション
  if (_state == VCStateMain) {
    int preHP = _characterManager->getHP();
    _enemyManager->nextTurn(_characterManager, false, false);
    CCObject* obj = NULL;
    CCArray* enemies = CCArray::create();
    CCARRAY_FOREACH(_enemyManager->getEnemies(), obj) {
      enemies->addObject(obj); // ここでshallowコピーを作る
    }
    CCARRAY_FOREACH(enemies, obj) {
      Enemy* enemy = (Enemy*)obj;
      if (enemy->getRow() < 0) {
        int damage = floor(0.5 + enemy->getAttack() * _characterManager->getLevelOffsetRate(enemy->getLevel(), _characterManager->getLevel()));
        _characterManager->damage(damage);
        _enemyManager->removeEnemy(enemy);
      }
    }
    int sub = abs(_characterManager->getHP() - preHP);
    SaveData::sharedData()->addCountFor(SaveDataCountKeyHitDamage, sub); // 被ダメージカウント
    _log->setCount(PlayLogKeyHitDamage, sub + _log->getCount(PlayLogKeyHitDamage)); // 被ダメージカウント
    
    if (_characterManager->getDamageInfoQueue()->size() > 0) {
      if (_characterManager->getShield()) { // 盾装備してたとき
        SEManager::sharedManager()->registerEffect(FileUtils::getFilePath("SE/guard.mp3").c_str());
        _characterManager->setShield(false); // 盾問答無用で外します
      }
    }
    this->addDamageEffect();
    this->updateGUI();
    
    // 盾を外すエフェクト
    if (!_characterManager->getShield()) {
      _effectLayer->addCutin(NULL, EffectLayerCutinTypeCastOff, _musicManager->getMusic()->getCurrentMainTrack()->getDuration());
    }
  }
  if (preTension != _characterManager->getTension()) { // テンションが変わってたら技の状態を更新
    _skin->getController()->updateSkills(_characterManager, _level, false);
  }
  _map->performOnBack(_characterManager, _enemyManager);
  _effectLayer->updateFocus(_enemyManager);
}

void MainScene::trackWillFinishPlaying(Music *music, Track *currentTrack, Track *nextTrack, int trackNumber) {
  if (_state == VCStateIntro) {
    _musicManager->setIntroCount(_musicManager->getIntroCount() + 1);
    int maxIntroCount = _musicManager->getMusicSet()->getIntroCount();
    if (_musicManager->getIntroCount() == maxIntroCount) { // イントロが終わったとき
      _musicManager->setIntroCount(0);
      _skin->getController()->setEnable(true);
      _characterManager->setRepeatCount(0);
      _skin->getController()->resetAllTriggers();
      if (_level->getLevel() == _initialLevel) {
        _map->performOnLevel(_characterManager, _enemyManager); // 初期レベルの時、スクリプトを呼んでやる
      }
      _state = VCStateMain;
    }
  }
  if (_state == VCStateFinish || _state == VCStateQTEFinish) {
    _musicManager->setFinishCount(_musicManager->getFinishCount() + 1);
    int maxFinishCount = _musicManager->getMusicSet()->getFinishCount();
    if (_musicManager->getFinishCount() == maxFinishCount) { // フィニッシュ曲が終わったとき
      _musicManager->setFinishCount(0);
      this->onFinishTracksCompleted();
    }
  }
  if (_state == VCStateMain) {
    Skill* skill = NULL;
    if (_characterManager->isPerforming()) {
      skill = _characterManager->getCurrentSkill();
    } else if (_effectLayer->getPopupWindow()) { // チュートリアルウィンドウが出ているとき
      _state = VCStateWindow;
      _skin->getController()->setEnable(false); // コントローラーを無効に
    } else {
      skill = _skin->getController()->currentTriggerSkill();
    }
    if (skill != NULL) {
      _log->setSkillCount(skill, _characterManager); // カウントを更新
    }
    _musicManager->pushNextTracks(skill, _currentSkillInfo);
    if (_isLevelUped) { // 前のターンでレベルが上がっていたら
      _isLevelUped = false;
      if (_level->getLevel() == _map->getMaxLevel() && _map->isBossStage()) { // 最高レベルのとき、かつボス面のとき
        // 道中フィニッシュ曲を流す。フィニッシュ曲が終わったらボス面に切り替えてイントロ曲を流す
        _state = VCStateFinish;
        _skin->getController()->setEnable(false);
        _musicManager->getMusic()->removeAllNextTracks();
        float musicDuration = _musicManager->getMusic()->getCurrentMainTrack()->getDuration();
        float duration = musicDuration * (_map->getWayMusic()->getFinishCount());
        _effectLayer->addWarning(duration);
        if (_musicManager->getMusicSet()->getFinishCount() == 0) {
          this->startBossBattle();
        } else {
          _musicManager->pushFinishTracks();
        }
      } else if (_level->getLevel() >= _map->getMaxLevel() + 1) { // 最大レベル + 1のとき
        _state = VCStateFinish;
        _skin->getController()->setEnable(false);
        _musicManager->getMusic()->removeAllNextTracks();
        if (_musicManager->getMusicSet()->getFinishCount() == 0) {
          this->gotoNextStage();
        } else {
          _enemyManager->removeAllNormalEnemies(); // 雑魚キャラを全滅させます
          MessageManager::sharedManager()->pushRandomMessageFromFunction("clear", _map, _characterManager, _enemyManager);
          _musicManager->pushFinishTracks();
        }
      }
    }
  } else if (_state == VCStateQTEWait) { // QTE待機中の時
    if (_qteTrigger && _qteTrigger->isButtonPressed()) {
      _musicManager->pushFinishTracks(); // finishTrack入れる
      this->removeChild(_qteTrigger, true);
      _qteTrigger->release();
      _qteTrigger = NULL;
      _musicManager->setMinDrumScore(0);
      _state = VCStateQTEFinish;
      Enemy* boss = _enemyManager->getBoss();
      CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/qte_attack.mp3").c_str());
      _effectLayer->addQTEAttack(boss);
      // ぷるぷるさせる
      CCArray* actions = CCArray::create();
      float duration = _musicManager->getMusic()->getCurrentMainTrack()->getDuration();
      const int length = 50;
      CCPoint origin = boss->getPosition();
      for (int i = 0; i < length; ++i) {
        float x = -4 + rand() % 8;
        float y = -10 + rand() % 20;
        CCPlace* move = CCPlace::create(ccpAdd(origin, ccp(x, y)));
        CCDelayTime* delay = CCDelayTime::create(duration * 2 / length);
        actions->addObject(CCSequence::create(move, delay, NULL));
      }
      boss->runAction(CCSequence::create(actions));
      MessageManager::sharedManager()->pushRandomMessageFromFunction("qte_attack", _map, _characterManager, _enemyManager);
    } else {
      _musicManager->pushQTETracks();
    }
  } else if (_state == VCStateQTEFinish) { // QTE終了時
    int count = _musicManager->getFinishCount();
    if (count == 2) { // 3小節目
      MessageManager::sharedManager()->pushRandomMessageFromFunction("qte_explosion", _map, _characterManager, _enemyManager); // 爆発メッセージ
      SaveData::sharedData()->addDefeatedCountForEnemy(_enemyManager->getBoss()->getSpecies()->getIdentifier().c_str()); // ボスの倒したカウンター増加
      _enemyManager->removeEnemy(_enemyManager->getBoss());
      _enemyManager->setBoss(NULL);
      CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("explosion.mp3").c_str()); // 爆発
      _enemyManager->removeAllNormalEnemies(); // ついでに雑魚キャラ全消去
    }
  } else if (_state == VCStateMapSelect) {
    Map* nextMap = _mapSelector->getSelectedMap();
    if (nextMap) {
      _state = VCStateMain;
      _skin->getController()->setEnable(true);
      this->removeChild(_mapSelector, true);
      this->changeMap(nextMap);
      _mapSelector->release();
      _mapSelector = NULL;
    } else {
      _musicManager->pushSilentTracks(); // 選択されてなかったら、次の小節も無音
    }
  } else if (_state == VCStateWindow) { // ウィンドウが出てたら
    _musicManager->pushNextTracks(NULL, _currentSkillInfo); // 常にwait
    if (!_effectLayer->getPopupWindow()) {
      _state = VCStateMain;
    }
  }
  
  SaveData::sharedData()->addCountFor(SaveDataCountKeyTurn); // 小節数を数えます
  this->updateGUI(); // GUI更新
}

void MainScene::trackDidFinishPlaying(Music *music, Track *finishedTrack, Track *nextTrack, int trackNumber) {
  switch (_state) {
    case VCStateMain:
    {
    // メインの動きを実行
    // この辺をリファクタリングする
    Skill* skill = _currentSkillInfo.skill;
    SkillPerformType performType = _currentSkillInfo.type;
    string name = _currentSkillInfo.skillTrackName;
    int preMP = _characterManager->getMP();
    int preExp = _characterManager->getExp();
    int getExp = 0;
    
    int sumDamage = 0;
    bool isHit = true; // ヒットしたかどうか
    /* 以下のとき、ヒットしていない
     1. 対象が自分以外の技を使用し、対象の全てについて
     ・盾やバリアに弾かれた
     　　　　　　 ・盾やバリアを破壊した場合、与ダメージが0でもヒットした扱いにする
     ・本来、ダメージを与えられる技を使ったはずなのに被ダメージが0である
     　　　　　   ・例えばノックバックはダメージが0でも、本来与えるダメージが0なのでヒットしている
     ・本来ダメージが与えられるはずなのに、耐性やレベル補正でダメージが0だった場合、ヒットしていない
     ・その技がその種族によって無効化されている
     */
    if (skill && performType == SkillPerformTypeSuccess) {
      
      CCArray* targets = _enemyManager->getTargets(skill);
      MessageManager::sharedManager()->pushRandomMessageFromSkill(skill, targets, _map, _characterManager, _enemyManager); // メッセージを追加する
      CCDictionary* info = _enemyManager->performSkill(skill, targets, _characterManager); // ここで経験値が貰える
      CCArray* enemies = (CCArray*)info->objectForKey("enemies");
      CCArray* damages = (CCArray*)info->objectForKey("damages");
      CCArray* damageTypes = (CCArray*)info->objectForKey("damageTypes");
      
      int enemyCount = enemies->count();
      isHit = skill->getRange() == SkillRangeSelf || targets->count() == 0; // 自分が対象もしくは誰もいなければ絶対に成功
      CCObject* obj = NULL;
      int i = 0;
      int deathCount = 0; // 倒した敵の数
      CCARRAY_FOREACH(enemies, obj) {
        Enemy* enemy = (Enemy*)obj;
        // ダメージが0かつ、元々ダメージのない技じゃないかつ、アイテムも破壊していないとき、ヒットしていない状態にしてやる
        int damage = ((CCInteger*)damages->objectAtIndex(i))->getValue();
        sumDamage += damage;
        DamageType damageType = (DamageType)((CCInteger*)damageTypes->objectAtIndex(i))->getValue();
        if (damage > 0 || damageType == DamageTypeBarrierBreak || damageType == DamageTypeShieldBreak || damageType == DamageTypeNoDamage) {
          isHit = true;
          if (damageType != DamageTypeDeath) {
            // ヒットしたとき、敵キャラを点滅させる。ぷるぷるさせる
            CCArray* actions = CCArray::create();
            CCPoint origin = enemy->getPosition();
            const int times = 6;
            const float blinkDuration = 0.05;
            if (damage == 0) {
              actions->addObject(CCDelayTime::create(blinkDuration * 2 * 3));
            } else {
              float scale = enemy->getCurrentScale(enemy->getRow());
              for (int i = 0; i < 10; ++i) {
                float x = -damage / 2 + rand() % damage * scale;
                float y = -damage / 2 + rand() % damage * scale;
                CCPlace* move = CCPlace::create(ccpAdd(origin, ccp(x, y)));
                CCDelayTime* delay = CCDelayTime::create(blinkDuration * 2 * 3 / times);
                actions->addObject(CCSequence::create(move, delay, NULL));
              }
            }
            actions->addObject(CCPlace::create(origin)); // 元に復帰
            enemy->runAction(CCSpawn::createWithTwoActions(CCRepeat::create(CCSequence::createWithTwoActions(CCFadeTo::create(blinkDuration, 64), CCFadeTo::create(blinkDuration, 255)), 3),
                                                           CCSequence::create(actions)));
          }
        }
        if (damageType == DamageTypeDeath) { // 敵キャラを殺したとき
          SaveData::sharedData()->addCountFor(SaveDataCountKeyDefeat); // 殺しカウント++
          deathCount += 1;
        }
        
        if (damageType != DamageTypeNoDamage) { // 威力のない技は表示しない
          _effectLayer->addDamageLabelOnEnemy(enemy, damage, DamageLabelTypeAttack);
        }
        
        // メッセージ追加
        if (enemyCount == 1) {
          if (damageType == DamageTypePhysicalResist) {
            MessageManager::sharedManager()->pushRandomMessageFromFunction("resist_physical", _map, _characterManager, _enemyManager);
          } else if (damageType == DamageTypeMagicalResist) {
            MessageManager::sharedManager()->pushRandomMessageFromFunction("resist_magical", _map, _characterManager, _enemyManager);
          } else if (damageType == DamageTypeShieldBreak) {
            MessageManager::sharedManager()->pushRandomMessageFromFunction("shield_physical_break", _map, _characterManager, _enemyManager);
          } else if (damageType == DamageTypeBarrierBreak) {
            MessageManager::sharedManager()->pushRandomMessageFromFunction("barrier_magical_break", _map, _characterManager, _enemyManager);
          } else if (damageType == DamageTypePhysicalInvalid) {
            MessageManager::sharedManager()->pushRandomMessageFromFunction("shield_physical_invalid", _map, _characterManager, _enemyManager);
          } else if (damageType == DamageTypeMagicalInvalid) {
            MessageManager::sharedManager()->pushRandomMessageFromFunction("barrier_magical_invalid", _map, _characterManager, _enemyManager);
          }
        }
        
        // 敵毎に効果音を鳴らす
        string fileName = "";
        switch (damageType) {
          case DamageTypeShieldBreak:
          case DamageTypeBarrierBreak:
            fileName = "shield_break.mp3";
            break;
          case DamageTypePhysicalInvalid:
            fileName = "shield_invalid.mp3";
            break;
          case DamageTypeMagicalInvalid:
            fileName = "barrier_invalid.mp3";
            break;
          case DamageTypePhysicalResist:
            fileName = "physical_resist.mp3";
            break;
          case DamageTypeMagicalResist:
            fileName = "magical_resist.mp3";
            break;
          default:
            break;
        }
        if (fileName.length() > 0) {
          SEManager::sharedManager()->registerEffect(fileName.c_str(), 0.15f);
        }
        ++i;
      }
      
      _log->setGraterCount(PlayLogKeyMaxDefeat, deathCount); // 同時に倒した数更新
      
      // ダメージ更新
      SaveData::sharedData()->addCountFor(SaveDataCountKeyAttackDamage, sumDamage);
      
      // 全体のSE
      if (enemyCount > 0 && skill->hasSE() && isHit) { // ヒットしたとき、SEがあればSEをならしてやる
        stringstream ss;
        ss << "SE/"<< skill->getIdentifier() << "_effect.mp3"; // 対象が自分、もしくは対象が1体以上いたとき、ダメージ効果音をならします
        SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath(ss.str().c_str()).c_str());
      } else if (skill->getRange() == SkillRangeSelf && skill->hasSE()) { // 対象が自分だけ、かつSEを持っているとき
        stringstream seStream;
        seStream << "SE/"<< skill->getIdentifier() << "_effect.mp3"; // 効果音をならします
        SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath(seStream.str().c_str()).c_str());
      } else if (enemies->count() == 0) { // 誰もいないときピロリ音
        SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("miss.mp3").c_str());
        MessageManager::sharedManager()->pushRandomMessageFromFunction("notarget", _map, _characterManager, _enemyManager); // ピロリメッセージ
      }
      
      _effectLayer->addSkillEffect(skill, enemies);
      if (!_characterManager->getShield()) {
        _effectLayer->addCutin(NULL, EffectLayerCutinTypeCastOff, _musicManager->getMusic()->getCurrentMainTrack()->getDuration());
      }
      
      _effectLayer->addCutin(skill, isHit ? (EffectLayerCutinType)skill->getCutinType() : EffectLayerCutinTypeFailure, _musicManager->getMusic()->getCurrentMainTrack()->getDuration());
      
      getExp = ((CCInteger*)info->objectForKey("exp"))->getValue();
    } else if (skill == NULL && _characterManager->getRepeatCountRaw() >= 3) {
      MessageManager::sharedManager()->pushRandomMessageFromFunction("noaction", _map, _characterManager, _enemyManager); // 3ターン何もしないメッセージ
    }
    
    if (_currentSkillInfo.type == SkillPerformTypeFailure) { // MP切れで失敗したとき
      MessageManager::sharedManager()->pushRandomMessageFromFunction("mpmiss", _map, _characterManager, _enemyManager); // MP切れメッセージ
      SaveData::sharedData()->addCountFor(SaveDataCountKeyMPMiss); // MP切れ
    }
    
    // レベルアップ判定
    if (this->checkLevelUp() ) {
      int currentLevel = _characterManager->getLevel();
      int skillCount = _level->getSkills((Character*)_characterManager->getCharacters()->objectAtIndex(0))->count() + _level->getSkills((Character*)_characterManager->getCharacters()->objectAtIndex(1))->count();
      SEManager::sharedManager()->registerEffect(FileUtils::getFilePath("SE/levelup.mp3").c_str());
      _musicManager->setIntroCount(0);
      _preLevel = currentLevel;
      MessageManager::sharedManager()->pushRandomMessageFromFunction("levelup", _map, _characterManager, _enemyManager); // レベルアップメッセージ
      if (!_map->isBossStage() || _map->getMaxLevel() != _level->getLevel()) {
        _map->performOnLevel(_characterManager, _enemyManager); // スクリプトを呼んでやる
      }
      _characterManager->updateParameters();
      this->setLevel(_map->createLevel(currentLevel, _characterManager));
      _enemyManager->setLevel(_level);
      int newSkillCount = _level->getSkills((Character*)_characterManager->getCharacters()->objectAtIndex(0))->count() + _level->getSkills((Character*)_characterManager->getCharacters()->objectAtIndex(1))->count();
      
      if (skillCount < newSkillCount) { // 新しくワザを覚えていたとき
        MessageManager::sharedManager()->pushRandomMessageFromFunction("new_skill", _map, _characterManager, _enemyManager); // ワザ取得メッセージ
      }
      
      this->updateGUI();
      
      CCSprite* levelup = CCSprite::create("levelup.png");
      levelup->setPosition(ccp(-100, 180));
      levelup->runAction(CCSequence::create(CCEaseSineIn::create(CCMoveTo::create(0.5f, ccp(240, 180))),
                                            CCDelayTime::create(1.0f),
                                            CCEaseSineIn::create(CCMoveTo::create(0.5f, ccp(680, 180))),
                                            CCRemoveFromParentAction::create(),
                                            NULL));
      _effectLayer->addChild(levelup);
      
      _enemyManager->removeAllEnemiesQueue();
      _isLevelUped = true;
    }
    
    // 固定モンスターテーブルを見て、モンスターを出現させます
    CCArray* fixed = _map->getFixedEnemies(preExp, preExp + getExp);
    if (fixed->count() > 0) {
      _enemyManager->pushEnemiesQueue(fixed);
    }
    
    _currentSkillInfo.skillTrackName = "";
    _currentSkillInfo.type = SkillPerformTypeNone;
    _currentSkillInfo.skill = NULL;
    
    // 技の発動タイミングで、コマンドをかっこよく光らせる
    if (skill) {
      SkillTrigger* trigger = _skin->getController()->getSkillTriggerFor(skill);
      if (trigger) {
        trigger->runBlinkAction(0.2f);
      }
    }
    
    // 床を更新する
    if (!this->isBossBattle()) {
      _skin->getGround()->nextFrame();
    }
    
    // ターンカウントを進める
    _log->addCount(PlayLogKeyTurn);
    
    _log->setGraterCount(PlayLogKeyMaxRepeatCount, _characterManager->getRepeatCountRaw()); // repeatCount追加
    ++_mapTurnCount;
    
    // テンション4段階で技を使ってたらフラッシュ
    if (skill && _characterManager->getTension() == 4 && skill->getIdentifier() != "tension") {
      BlinkLayer* bLayer = new BlinkLayer(ccc4(255, 255, 255, 255), 0.1f);
      bLayer->autorelease();
      this->addChild(bLayer, MainSceneZOrderUI);
    }
    
    // このターンにテンション使ってないときreset
    if (_characterManager->getLastSkill() != NULL && !_characterManager->getLastSkill()->isKeepTension()) {
      _characterManager->resetTension();
    }
    _effectLayer->setTensionEffect(_characterManager->getTension());
    if (_characterManager->getLastSkill() != NULL && _characterManager->getLastSkill()->getIdentifier() == "change") { // チェンジ使ったとき
      _effectLayer->setCharacterEffect(_characterManager->getCurrentCharacter());
    }
    
    // スキルがなかった場合は、現在のトリガー状態を次のターンに持ち越すためにトリガー位置をリセットしません
    // スキルがあった場合はトリガー位置をリセットします
    _skin->getController()->updateSkills(_characterManager, _level, skill != NULL);
    
    this->updateGUI(); // GUI更新
    
    if (preMP > 0 && _characterManager->getMP() == 0) {
      MessageManager::sharedManager()->pushRandomMessageFromFunction("empty", _map, _characterManager, _enemyManager);
    }
    
    if (!_characterManager->isPerforming()) {
      _enemyManager->purgeAllTrash();
    }
    if (_enemyManager->getBoss() && _enemyManager->getBoss()->getHP() <= 0) { // ボスが死んでたらQTEに移行する
      _state = VCStateQTEWait;
      MessageManager::sharedManager()->pushRandomMessageFromFunction("qte_wait", _map, _characterManager, _enemyManager); // QTEメッセージ
      _musicManager->setMinDrumScore(4);
      _skin->getController()->setEnable(false);
      _qteTrigger = new QTETrigger(_enemyManager);
      _effectLayer->getFocus()->setVisible(false); // フォーカス非表示にする
      this->addChild(_qteTrigger, MainSceneZOrderUI);
      SEManager::sharedManager()->registerEffect(FileUtils::getFilePath("qte.mp3").c_str());
    }
    }
      break;
    default:
      break;
  }
  
  // マーカーを再同期
  _skin->getStatusLayer()->setMarkerDuration(_musicManager->getMusic()->getTrack(0)->getDuration() / 4.0f);
  _effectLayer->updateFocus(_enemyManager);
  _map->performOnFinishPlaying(_characterManager, _enemyManager);
}

void MainScene::registerWithTouchDispatcher() {
  CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 100, true);
}

bool MainScene::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent) {
  if (_state == VCStateWindow) {
    PopupWindow* layer = _effectLayer->getPopupWindow();
    if (layer) {
      if (layer->isMessageEnded()) { // メッセージ終わってたら次のページ
        layer->nextPage();
      } else {
        layer->onWindowTouched(); // そうじゃなきゃメッセージ終了
      }
      return true;
    }
  }
  return false;
}

void MainScene::updateGUI() {
  StatusLayer* statusLayer = _skin->getStatusLayer();
  statusLayer->setCurrentHP(_characterManager->getHP());
  statusLayer->setMaxHP(_characterManager->getMaxHP());
  statusLayer->setCurrentMP(_characterManager->getMP());
  statusLayer->setMaxMP(_characterManager->getMaxMP());
  statusLayer->setLevel(_characterManager->getLevel());
  int next = _characterManager->getExpWithLevel(_level->getLevel() + 1);
  statusLayer->setExp(_characterManager->getExp(), next);
}

bool MainScene::checkLevelUp() {
  int currentLevel = _characterManager->getLevel();
  if (currentLevel > _map->getMaxLevel() + 1) {
    int maxExp = _characterManager->getExpWithLevel(_map->getMaxLevel() + 2) - 1;
    int sub = maxExp - _characterManager->getExp(); // オーバー
    _characterManager->addExp(sub); // オーバーした分だけ引く
  }
  return (currentLevel != _preLevel); // レベルが上がったとき
}

void MainScene::onGameOver() {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("Music/general/gameover.mp3").c_str());
  CCDictionary* dict = CCDictionary::create();
  dict->setObject(CCString::create(_characterManager->getCurrentCharacter()->getName()), "chara");
  MessageManager::sharedManager()->pushRandomMessageFromFunction("death", _map, _characterManager, _enemyManager);
  _state = VCStateGameOver;
  GameOverLayer* gameover = new GameOverLayer(this);
  gameover->setMainBackScene(_backScene);
  this->addChild(gameover, MainSceneZOrderUI);
  gameover->autorelease();
  _musicManager->getMusic()->pause();
  _skin->getController()->setVisible(false);
  SaveData::sharedData()->addCountFor(SaveDataCountKeyDead); // 死亡回数をカウント
  _log->addCount(PlayLogKeyDead);
}

void MainScene::addDamageEffect() {
  // 被ダメージに応じてラベルなど表示
  bool isDead = false;
  bool isShield = false;
  int sumDamage = 0;
  int i = 0;
  std::queue<DamageInfo>* queue = _characterManager->getDamageInfoQueue();
  int queueCount = queue->size();
  while (!queue->empty()) { // キューが空になるまで取り出す
    DamageInfo info = queue->front();
    queue->pop();
    int damage = info.damage;
    DamageType damageType = info.damageType;
    _effectLayer->addDamageLabel(damage, i, DamageLabelTypeHit);
    sumDamage += damage;
    ++i;
    if (damageType == DamageTypeDeath) {
      isDead = true;
    } else if (damageType == DamageTypeShield) {
      isShield = true;
    }
  }
  // 総ダメージに応じて画面を揺らしてやる
  
  if (sumDamage > 0) {
    // 画面点滅させて音を鳴らす
    if (sumDamage < 5) {
      SEManager::sharedManager()->registerEffect(FileUtils::getFilePath("SE/damage0.mp3").c_str());
    } else if (sumDamage < 10) {
      SEManager::sharedManager()->registerEffect(FileUtils::getFilePath("SE/damage1.mp3").c_str());
    } else {
      SEManager::sharedManager()->registerEffect(FileUtils::getFilePath("SE/damage2.mp3").c_str());
    }
    BlinkLayer* bLayer = new BlinkLayer(ccc4(255, 0, 0, 255), 0.05f);
    bLayer->autorelease();
    this->addChild(bLayer, MainSceneZOrderUI);
    // ついでに画面もゆらしちゃう
    const float FPS = 60.0;
    const int shakeRange = 15;
    CCArray* actions = CCArray::create();
    for (int i = 0; i < FPS / 2; ++i) {
      CCMoveTo* move = CCMoveTo::create(1.0 / FPS, ccp(sumDamage * (-shakeRange / 2 + rand() % shakeRange), sumDamage * (-shakeRange / 2 + rand() % shakeRange)));
      actions->addObject(move);
    }
    CCMoveTo* reset = CCMoveTo::create(0, ccp(0, 0));
    actions->addObject(reset);
    this->runAction(CCSequence::create(actions));
  } else if (sumDamage == 0 && queueCount > 0 && !isShield) { // 0のとき、かつqueueが空だったとき
    SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/guard.mp3").c_str());
    MessageManager::sharedManager()->pushRandomMessageFromFunction("guard", _map, _characterManager, _enemyManager); // ガードメッセージ
  }
  if (isDead) { // 死んだとき
    this->onGameOver();
  }
}

void MainScene::changeMap(Map* nextMap) {
  this->changeMap(nextMap, nextMap->getInitialLevel());
}

void MainScene::changeMap(Map* nextMap, int initialLevel) {
  bool init = _map == NULL;
  if (_map) {
    // 前の背景画像削除
    if (_map->getBackground()) {
      this->removeChild(_map->getBackground(), true);
    }
    _map->release();
    CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
    CCTextureCache::sharedTextureCache()->removeAllTextures();
  }
  nextMap->retain();
  _log->getMapHistory()->addObject(CCString::create(nextMap->getIdentifier())); // マップ履歴にマップのIdentifier追加
  _map = nextMap;
  this->setLevel(nextMap->createLevel(initialLevel, _characterManager)); // レベルを生成する

  _enemyManager->setLevel(_level); // レベルをセット
  _enemyManager->removeAllEnemiesQueue(); // キューを初期化
  _mapTurnCount = 0; // マップカウント0に戻す
  // 背景画像を設置
  CCDirector* director = CCDirector::sharedDirector();
  CCSprite* background = _map->getBackground();
  if (background) {
    background->setPosition(ccp(director->getWinSize().width / 2.0, 221.5));
    this->addChild(background, MainSceneZOrderMapBackground);
  }
  _state = VCStateIntro;
  this->changeMusic(_map->getCurrentMusic(_level), true);
  this->changeSkin(_map->getSkin(), true);
  
  _musicManager->setIntroCount(0);
  _musicManager->setFinishCount(0);
   _musicManager->pushIntroTracks();
   
  _skin->getController()->setEnable(false);
  _characterManager->setRepeatCount(0); // repeatCountをリセット
  this->updateGUI();
  _map->performOnLoad(_characterManager, _enemyManager);
  if (!init) {
    _effectLayer->addWaitMarker(_musicManager->getMusic()->getCurrentMainTrack()->getDuration() * _musicManager->getMusicSet()->getIntroCount());
  }
  CCTextureCache::sharedTextureCache()->removeUnusedTextures();
  Species::purgeSpeciesCache();
  SimpleAudioEngine::sharedEngine()->unloadAllEffect();
}

void MainScene::changeSkin(Skin *newSkin, bool crossFade) {
  // スキンの切り替え
  // 後始末
  const float kCrossFadeSpeed = 1.0f;
  if (_skin != NULL) {
    newSkin->setController(_skin->getController()); // 古いコントローラーを受け渡す
    _skin->getController()->updateSkills(_characterManager, _level, true); // スキン更新
    if (crossFade) {
      CCArray* nodes = CCArray::create();
      if (_skin->getBackground()) nodes->addObject(_skin->getBackground());
      nodes->addObject(_skin->getGround());
      nodes->addObject(_skin->getStatusLayer());
      CCObject* obj = NULL;
      // まとめてフェードアウトを設定
      CCARRAY_FOREACH(nodes, obj) {
        CCNode* node = (CCNode*)obj;
        node->runAction(CCSequence::create(CCFadeOut::create(kCrossFadeSpeed),
                                           CCRemoveFromParentAction::create(),
                                           NULL));
      }
    } else {
      this->removeChild(_skin->getBackground(), true);
      this->removeChild(_skin->getGround(), true);
      this->removeChild(_skin->getStatusLayer(), true);
    }
    _skin->release(); // 今のスキンをReleaseします
  }
  _skin = newSkin; // 新しいマップのスキンを格納します
  _skin->retain();
  CCArray* nodes = CCArray::create();
  CCSprite* background = _skin->getBackground();
  if (background) {
    CCDirector* director = CCDirector::sharedDirector();
    background->setPosition(ccp(director->getWinSize().width / 2.0f, director->getWinSize().height / 2.0f));
    this->addChild(background, MainSceneZOrderBackground);
    nodes->addObject(background);
  }
  nodes->addObject(_skin->getGround());
  nodes->addObject(_skin->getStatusLayer());
  this->addChild(_skin->getGround(), MainSceneZOrderGround);
  this->addChild(_skin->getStatusLayer(), MainSceneZOrderStatus);
  if (crossFade) {
    if (background) {
      background->setOpacity(0.0f);
      background->runAction(CCFadeIn::create(kCrossFadeSpeed));
    }
  }
  _effectLayer->reloadFocus(_skin);
}

void MainScene::startBossBattle() {
  _skin->getController()->setEnable(false);
  _state = VCStateIntro; // イントロに移行
  this->changeMusic(_map->getCurrentMusic(_level), false);
  _characterManager->setRepeatCount(0);
  _skin->getController()->setEnable(false);
  MessageManager::sharedManager()->pushRandomMessageFromFunction("warning", _map, _characterManager, _enemyManager); // ボス出現メッセージ
  _musicManager->pushIntroTracks();
}

void MainScene::gotoNextStage() {
  if (_state == VCStateFinish) {
    CCArray* maps = _map->getNextMaps();
    CCAssert(maps->count() > 0, "Next Map must be larger than 0.");
    if (maps->count() == 1) {
      this->changeMap((Map*)maps->objectAtIndex(0));
    } else if (maps->count() >= 2) {
      _mapSelector = new MapSelector(maps);
      _skin->getController()->setEnable(false);
      this->addChild(_mapSelector, MainSceneZOrderUI);
      _state = VCStateMapSelect;
      MessageManager::sharedManager()->pushRandomMessageFromFunction("map_select", _map, _characterManager, _enemyManager); // マップセレクター
    }
  }
}

void MainScene::onFinishTracksCompleted() {
  if (_state == VCStateQTEFinish) { // QTEFinishのとき
    _enemyManager->removeAllNormalEnemies();
    _musicManager->getMusic()->stop();
    if (_log->getMapHistory()->count() == 3) { // マップが3のとき
      // おそらくボス撃破後なので、エンディングに移行します
      string endingScript = _map->getEndingName();
      CCAssert(endingScript.length() != 0, "Ending Script is not defined.");
      EndingScene* endingLayer = new EndingScene(endingScript.c_str());
      endingLayer->autorelease();
      endingLayer->setUserObject(_log); // PlayLogをユーザーデータに
      CCScene* ending = CCScene::create();
      ending->addChild(endingLayer);
      _log->checkAchievementsOnClear(_characterManager, _enemyManager);
      SaveData::sharedData()->setClearedForMap(_map->getIdentifier().c_str());
      SaveData::sharedData()->addCountFor(SaveDataCountKeyClear); // クリア回数
      _map->performOnClear(_characterManager, _enemyManager);
      this->teardown();
      CCTransitionFade* fade = CCTransitionFade::create(7.0f, ending, ccc3(255, 255, 255));
      CCDirector::sharedDirector()->replaceScene(fade);
    } else { // それ以外の時、フリープレイっぽいのでフリープレイ画面に戻します
      CCScene* freePlay = FreePlayScene::scene("freeplay", false);
      CCTransitionFade* fade = CCTransitionFade::create(7.0f, freePlay, ccc3(255, 255, 255));
      CCDirector::sharedDirector()->replaceScene(fade);
    }
  } else if (_map->isBossStage() && _level->getLevel() == _map->getMaxLevel()) { // ボスステージで、現在が最高レベルの時
    // ボス戦を開始します
    this->startBossBattle();
  } else if (_level->getLevel() >= _map->getMaxLevel() + 1 && _map->getNextMaps()->count() > 0) { // 最高レベルの次の時で、次のマップが存在するとき
    // 次のステージに移動します
    SaveData::sharedData()->setClearedForMap(_map->getIdentifier().c_str()); // クリアした
    this->gotoNextStage();
    _map->performOnClear(_characterManager, _enemyManager);
  }
}

void MainScene::setPause(bool pause) {
  CCScheduler* scheduler = CCDirector::sharedDirector()->getScheduler();
  if (pause && !this->getChildByTag(PAUSE_LAYER_TAG)) {
    PauseLayer* layer = new PauseLayer(this);
    layer->setMainBackScene(_backScene);
    layer->autorelease();
    CCSet* targets = scheduler->pauseAllTargets();
    targets->removeObject(this);
    layer->setPausedTargets(targets);
    if (_qteTrigger) {
      _qteTrigger->getMenu()->setEnabled(false);
    }
    if (_effectLayer->getPopupWindow()) {
      _effectLayer->getPopupWindow()->setEnabled(false);
    }
    _musicManager->getMusic()->pause();
    this->addChild(layer, 1000, PAUSE_LAYER_TAG);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/pause.mp3").c_str());
  } else {
    PauseLayer* layer = (PauseLayer*)this->getChildByTag(PAUSE_LAYER_TAG);
    if (layer) {
      _musicManager->getMusic()->play();
      if (_effectLayer->getPopupWindow()) {
        _effectLayer->getPopupWindow()->setEnabled(true);
      }
      scheduler->resumeTarget(this);
      scheduler->resumeTargets(layer->getPausedTargets());
      layer->setPausedTargets(NULL);
      this->removeChildByTag(PAUSE_LAYER_TAG, true);
      if (_qteTrigger) {
        _qteTrigger->getMenu()->setEnabled(true);
      }
    }
  }
}

void MainScene::changeMusic(MusicSet* mSet, bool enablePreload) {
  _musicManager->setMusicSet(mSet); // 音楽セットを切り替える
  if (enablePreload) {
    _musicManager->preloadAllTracks(_characterManager, _level); // 曲データを読む
  }
  _effectLayer->addMusicInfo(_map, _level);
}

VCState MainScene::getState () {
  return _state;
}

bool MainScene::isBossBattle() {
  return _map && _map->isBossStage() && _level->getLevel() == _map->getMaxLevel();
}

PlayLog* MainScene::getPlayLog() {
  return _log;
}

void MainScene::setPlayLog(PlayLog* log) {
  if (_log) {
    _log->release();
  }
  _log = log;
  if (log) {
    log->retain();
  }
}

MainBackScene MainScene::getBackScene() {
  return _backScene;
}

void MainScene::setBackScene(MainBackScene backScene) {
  _backScene = backScene;
}

void MainScene::setLevel(Level* lv) {
  if (_level) {
    _level->release();
  }
  _level = lv;
  if (lv) {
    lv->retain();
  }
}

void MainScene::setIsContinue(bool c) {
  _isContinue = c;
}