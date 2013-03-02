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
  MainSceneZOrderDamageLabel,
  MainSceneZOrderEffect,
  MainSceneZOrderCutIn,
  MainSceneZOrderMessageWindow,
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
  if ( !CCLayer::init() ) {
    return false;
  }
  Music* music = new Music(3);
  music->autorelease();
  music->setTrackDidBackFunction(boost::bind(&MainScene::trackDidBack, this, _1, _2, _3));
  music->setTrackDidFinishFunction(boost::bind(&MainScene::trackDidFinishPlaying, this, _1, _2, _3, _4));
  music->setTrackWillFinishFunction(boost::bind(&MainScene::trackWillFinishPlaying, this, _1, _2, _3, _4));
  
  _skin = NULL;
  _effectLayer = EffectLayer::sharedLayer();
  _effectLayer->retain();
  
  _pausedTargets = NULL;
  
  _currentSkillInfo.skillTrackName = "";
  _currentSkillInfo.type = SkillPerformTypeNone;
  _currentSkillInfo.skill = NULL;
  
  _turnCount = 0;
  _mapTurnCount = 0;
  
  //LuaObject* setting = LuaObject::create("Script/setting");
  
  CCDirector* director = CCDirector::sharedDirector();
  
  // EnemyManager
  _enemyManager = EnemyManager::create();
  _enemyManager->retain();
  
  _focus = CCSprite::create(FileUtils::getFilePath("Image/focus.png").c_str());
  _focus->retain();
  _focus->setVisible(false);
  _focus->setAnchorPoint(ccp(0.5f, 0.0f));
  this->addChild(_focus, MainSceneZOrderFocus);
  
  _characterManager = new CharacterManager();
  CCSize size = director->getWinSize();
  _musicManager = new MusicManager(music, NULL, _enemyManager, _characterManager);
  _state = VCStateIntro;
  
  _messageWindow = new MessageWindow(FONT_NAME, 16, CCSizeMake(300, 40));
  _messageWindow->setPosition(ccp(director->getWinSize().width / 2.0f, director->getWinSize().height - 70));
  MessageManager::sharedManager()->setDefaultMessageWindow(_messageWindow);
  this->addChild(_messageWindow, MainSceneZOrderMessageWindow);
  
  _mapSelector = NULL;
  
  this->scheduleUpdate();
  
  Skin* skin = map->getSkin();
  Controller* controller = new Controller(skin->getPrefix().c_str());
  controller->autorelease();
  skin->setController(controller);
  
  this->changeMap(map); // マップの設定
  _characterManager->setLevel(_level->getLevel()); // 初期レベル設定
  
  this->addChild(_enemyManager, MainSceneZOrderEnemyManager);
  this->addChild(_skin->getController(), MainSceneZOrderController);
  this->updateGUI();
  _skin->getController()->updateSkills(_characterManager, _level);
  
  _qteTrigger = NULL;
  _isLevelUped = false;
  _preLevel = _level->getLevel();
  
  this->addChild(_effectLayer, MainSceneZOrderEffect);
  
  this->setTouchEnabled(true);
  
  return true;
}

MainScene::~MainScene() {
  _musicManager->getMusic()->stop();
  _map->release();
  _messageWindow->release();
  _musicManager->release();
  _enemyManager->release();
  _characterManager->release();
  _skin->release();
  _focus->release();
  if (_mapSelector != NULL) {
    _mapSelector->release();
  }
  if (_pausedTargets != NULL) {
    _pausedTargets->release();
  }
  if (_qteTrigger != NULL) {
    _qteTrigger->release();
  }
  _effectLayer->removeAllChildrenWithCleanup(true);
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
  _skin->getController()->setEnable(false);
  _musicManager->getMusic()->play();
  _skin->getStatusLayer()->setMarkerDuration(_musicManager->getMusic()->getTrack(0)->getDuration() / 4.0f);
  CCDictionary* dict = CCDictionary::create();
  dict->setObject(CCString::create(_characterManager->getCurrentCharacter()->getName()), "chara");
  MessageManager::sharedManager()->pushRandomMessageFromLua("welcome", dict);
}

void MainScene::trackDidBack(Music *music, Track *currentTrack, int trackNumber) {
  if (_state == VCStateMain) {
    _enemyManager->nextTurn(_characterManager);
    CCObject* obj = NULL;
    CCARRAY_FOREACH(_enemyManager->getEnemies(), obj) {
      Enemy* enemy = (Enemy*)obj;
      if (enemy->getRow() < 0) {
        int damage = floor(0.5 + enemy->getAttack() * _characterManager->getLevelOffsetRate(enemy->getLevel(), _characterManager->getLevel()));
        _characterManager->damage(damage);
        _enemyManager->removeEnemy(enemy);
      }
    }
    
    this->addDamageEffect();
    this->updateFocus();
    this->updateGUI();
  }
}

void MainScene::trackWillFinishPlaying(Music *music, Track *currentTrack, Track *nextTrack, int trackNumber) {
  if (_state == VCStateIntro) {
    _musicManager->setIntroCount(_musicManager->getIntroCount() + 1);
    int maxIntroCount = _musicManager->getMusicSet()->getIntroCount();
    if (_musicManager->getIntroCount() == maxIntroCount) { // イントロが終わったとき
      _musicManager->setIntroCount(0);
      _skin->getController()->setEnable(true);
      if (_level->getLevel() == _map->getInitialLevel()) {
        _map->performOnLevel(_level->getLevel(), _characterManager, _enemyManager); // 初期レベルの時、スクリプトを呼んでやる
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
    }else {
      skill = _skin->getController()->currentTriggerSkill();
      //_controller->resetAllTriggers(); // このタイミングでトリガーをOFFにしてやる
    }
    _musicManager->pushNextTracks(skill, _currentSkillInfo);
    if (_isLevelUped) { // 前のターンでレベルが上がっていたら
      _isLevelUped = false;
      if (_level->getLevel() == _map->getMaxLevel() && _map->isBossStage()) { // 最高レベルのとき、かつボス面のとき
        // 道中フィニッシュ曲を流す。フィニッシュ曲が終わったらボス面に切り替えてイントロ曲を流す
        _state = VCStateFinish;
        _skin->getController()->setEnable(false);
        _musicManager->getMusic()->removeAllNextTracks();
        _musicManager->pushFinishTracks();
      } else if (_level->getLevel() >= _map->getMaxLevel() + 1) { // 最大レベル + 1のとき
        _state = VCStateFinish;
        _skin->getController()->setEnable(false);
        _musicManager->getMusic()->removeAllNextTracks();
        if (_musicManager->getMusicSet()->getFinishCount() == 0) {
          this->gotoNextStage();
        } else {
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
      // 攻撃エフェクト
      CCSprite* effect = CCSprite::create((string("attack") + string("0.png")).c_str());
      CCAnimation* animation = CCAnimation::create();
      CCRect rect;
      CCPoint position = ccpAdd(boss->getPosition(), ccp(0, boss->getContentSize().height * boss->getCurrentScale(boss->getRow()) * 0.5f));
      rect = CCRectMake(0, 0, 400, 400);
      effect->setPosition(position);
      effect->setScale(boss->getScale());
      for (int i = 0; i < 6; ++i) {
        const char* frameName = (string("attack") + lexical_cast<string>(i) + string(".png")).c_str();
        animation->addSpriteFrame(CCSpriteFrame::create(FileUtils::getFilePath(frameName).c_str(), rect));
      }
      animation->setDelayPerUnit(2.0 / 60.0);
      effect->runAction(CCSequence::create(CCAnimate::create(animation),
                                           CCFadeOut::create(0.1f),
                                           CCRemoveFromParentAction::create(),
                                           NULL));
      _enemyManager->addChild(effect, MainSceneZOrderEffect);
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
    } else {
      _musicManager->pushQTETracks();
    }
  } else if (_state == VCStateQTEFinish) { // QTE終了時
    int count = _musicManager->getFinishCount();
    if (count == 2) { // 3小節目
      _enemyManager->removeEnemy(_enemyManager->getBoss());
      _enemyManager->setBoss(NULL);
      CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("explosion.mp3").c_str());
    }
  } else if (_state == VCStateMapSelect) {
    Map* nextMap = _mapSelector->getSelectedMap();
    if (nextMap) {
      _state = VCStateMain;
      _skin->getController()->setEnable(true);
      this->removeChild(_mapSelector, true);
      _mapSelector->release();
      _mapSelector = NULL;
      this->changeMap(nextMap);
    } else {
      _musicManager->pushSilentTracks(); // 選択されてなかったら、次の小節も無音
    }
  } else if (_state == VCStateWindow) { // ウィンドウが出てたら
    _musicManager->pushNextTracks(NULL, _currentSkillInfo); // 常にwait
    if (!_effectLayer->getPopupWindow()) {
      _state = VCStateMain;
    }
  }
  
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
    int preExp = _characterManager->getExp();
    int getExp = 0;
    
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
      CCDictionary* info = _enemyManager->performSkill(skill, targets, _characterManager); // ここで経験値が貰える
      CCArray* enemies = (CCArray*)info->objectForKey("enemies");
      CCArray* damages = (CCArray*)info->objectForKey("damages");
      CCArray* damageTypes = (CCArray*)info->objectForKey("damageTypes");
      int enemyCount = enemies->count();
      for (int i = 0; i < enemyCount; ++i) {
        isHit = true;
        Enemy* enemy = (Enemy*)enemies->objectAtIndex(i);
        CCLabelAtlas* damageLabel = CCLabelAtlas::create(boost::lexical_cast<string>(((CCInteger*)damages->objectAtIndex(i))->getValue()).c_str(),
                                                         FileUtils::getFilePath("Image/damage_number.png").c_str(), 50, 100, '0');
        // ダメージが0かつ、元々ダメージのない技じゃないかつ、アイテムも破壊していないとき、ヒットしていない状態にしてやる
        int damage = ((CCInteger*)damages->objectAtIndex(i))->getValue();
        DamageType damageType = (DamageType)((CCInteger*)damageTypes->objectAtIndex(i))->getValue();
        if (damage == 0 && damageType != DamageTypeBarrierBreak && damageType != DamageTypeShieldBreak && damageType != DamageTypeNoDamage) {
          isHit = false;
        } else if (damageType == DamageTypeDisable) {
          isHit = false;
        } else if (damageType != DamageTypeDeath) {
          // ヒットしたとき、敵キャラを点滅させる
          enemy->runAction(CCRepeat::create(CCSequence::createWithTwoActions(CCFadeTo::create(0.05, 64), CCFadeTo::create(0.05, 255)), 3));
        }
        damageLabel->setPosition(enemy->getPosition());
        float scale = enemy->getCurrentScale(enemy->getRow());
        damageLabel->setScale(scale);
        this->addChild(damageLabel, MainSceneZOrderDamageLabel);
        damageLabel->runAction(CCSequence::create(CCFadeIn::create(0.2),
                                                  CCDelayTime::create(0.5),
                                                  CCFadeOut::create(0.2),
                                                  CCRemoveFromParentAction::create(),
                                                  NULL));
      }
      
      // メッセージを追加する
      CCArray* messages = skill->getMessages();
      if (messages->count() > 0) {
        CCString* str = (CCString*)messages->randomObject();
        // この辺の実装酷いからなんとかする
        CCDictionary* dict = CCDictionary::create();
        dict->setObject(CCString::create(_characterManager->getCurrentCharacter()->getName()), "chara");
        MessageManager::sharedManager()->pushMessage(str->getCString(), dict);
      }
      if (_currentSkillInfo.type == SkillPerformTypeFailure) {
        MessageManager::sharedManager()->pushRandomMessageFromLua("empty"); // MP切れメッセージ
      }
      
      _effectLayer->addSkillEffect(skill, enemies);
      _effectLayer->addCutin(skill, isHit, _musicManager->getMusic()->getCurrentMainTrack()->getDuration());
      
      if (isHit) {
        // ヒットしたとき、SEがあればSEをならしてやる
        if (enemies->count() > 0) { // 対象が1体以上いるとき
          DamageType damageType = (DamageType)((CCInteger*)damageTypes->objectAtIndex(0))->getValue();
          stringstream seStream;
          // 今は当たった敵1体目のダメージタイプをとってきてならしているが、
          // 複数体に同時に当たったときは遅延して順番にならしても良さそう
          if (damageType == DamageTypeShieldBreak) {
            SEManager::sharedManager()->registerEffect(FileUtils::getFilePath("shield_break.mp3").c_str());
          } else if (damageType == DamageTypeBarrierBreak) {
            SEManager::sharedManager()->registerEffect(FileUtils::getFilePath("barrier_break.mp3").c_str());
          } else if (skill->hasSE()) {
            // 対象が自分、もしくは対象が1体以上いたとき、ダメージ効果音をならします
            seStream << "SE/"<< skill->getIdentifier() << "_effect.mp3";
            SEManager::sharedManager()->registerEffect(FileUtils::getFilePath(seStream.str().c_str()).c_str());
          }
        }  else if (skill->getRange() == SkillRangeSelf && skill->hasSE()) { // 対象が自分だけ、かつSEを持っているとき
          stringstream seStream;
          // 効果音をならします
          seStream << "SE/"<< skill->getIdentifier() << "_effect.mp3";
          SEManager::sharedManager()->registerEffect(FileUtils::getFilePath(seStream.str().c_str()).c_str());
        }
      } else if (!isHit) { // ヒットしていないとき、強制的にミス音にする
        if (enemyCount == 0) {
          // 誰もいないときピロリ音
          SEManager::sharedManager()->registerEffect(FileUtils::getFilePath("miss.caf").c_str());
        } else {
          DamageType damageType = (DamageType)((CCInteger*)damageTypes->objectAtIndex(0))->getValue();
          if (damageType == DamageTypePhysicalInvalid) {
            // 1体だけ敵がいるのに当たらず、盾持ちだったとき
            SEManager::sharedManager()->registerEffect(FileUtils::getFilePath("shield_invalid.mp3").c_str());
          } else if (damageType == DamageTypeMagicalInvalid) {
            // バリア持ちだったとき
            SEManager::sharedManager()->registerEffect(FileUtils::getFilePath("barrier_invalid.mp3").c_str());
          }
        }
        
      }
      getExp = ((CCInteger*)info->objectForKey("exp"))->getValue();
    } else if (performType == SkillPerformTypeNone) {
      // 何も実行しなかったとき
      // MP回復 コマンド化したのでコメントアウトしておきます
      //_characterManager->addMP(1);
    }
    if (this->checkLevelUp() ) {
      int currentLevel = _characterManager->getLevel();
      SEManager::sharedManager()->registerEffect(FileUtils::getFilePath("SE/levelup.mp3").c_str());
      _musicManager->setIntroCount(0);
      _preLevel = currentLevel;
      _map->performOnLevel(currentLevel, _characterManager, _enemyManager); // スクリプトを呼んでやる
      //_characterManager->updateParameters();
      _level = _map->createLevel(currentLevel, _characterManager);
      _enemyManager->setLevel(_level);
      //this->updateGUI();
      
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
    _skin->getGround()->nextFrame();
    
    // ターンカウントを進める
    ++_turnCount;
    ++_mapTurnCount;
    // このターンにテンション使ってないときreset
    if (_characterManager->getLastSkill() != NULL && _characterManager->getLastSkill()->getIdentifier() != "tension") {
      _characterManager->resetTension();
    }
    _effectLayer->setTensionEffect(_characterManager->getTension());
    if (_characterManager->getLastSkill() != NULL && _characterManager->getLastSkill()->getIdentifier() == "change") { // チェンジ使ったとき
      _effectLayer->setCharacterEffect(_characterManager->getCurrentCharacter());
    }
    
    if (skill) {
      _skin->getController()->updateSkills(_characterManager, _level);
    }
    
    this->updateFocus();
    
    if (!_characterManager->isPerforming()) {
      _enemyManager->purgeAllTrash();
    }
    if (_enemyManager->getBoss() && _enemyManager->getBoss()->getHP() <= 0) { // ボスが死んでたらQTEに移行する
      _state = VCStateQTEWait;
      _musicManager->setMinDrumScore(4);
      _skin->getController()->setEnable(false);
      _qteTrigger = new QTETrigger(_enemyManager);
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
}

void MainScene::registerWithTouchDispatcher() {
  CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool MainScene::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent) {
  if (_state == VCStateWindow) {
    PopupWindow* layer = _effectLayer->getPopupWindow();
    if (!layer) return false;
    if (layer->isLastPage()) { // 最終ページだったら
      layer->runAction(CCSequence::create(CCScaleTo::create(0.3f, 0),
                                          CCRemoveFromParentAction::create(),
                                          NULL));
      _state = VCStateMain;
    } else { // まだページが残っていたら
      layer->nextPage();
    }
  }
  return true;
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
  MessageManager::sharedManager()->pushRandomMessageFromLua("death", dict);
  _state = VCStateGameOver;
  GameOverLayer* gameover = new GameOverLayer(this);
  this->addChild(gameover, MainSceneZOrderUI);
  gameover->autorelease();
  _musicManager->getMusic()->pause();
  _skin->getController()->setVisible(false);
}

void MainScene::updateFocus() {
  Enemy* nearest = _enemyManager->getNearestEnemy();
  if (nearest) {
    _focus->setVisible(true);
    _focus->setPosition(ccpAdd(nearest->getPosition(), ccp(0, nearest->getContentSize().height * nearest->getCurrentScale(nearest->getRow()) * 0.8)));
    _focus->setScale(nearest->getCurrentScale(nearest->getRow()));
  } else {
    _focus->setVisible(false);
  }
}

void MainScene::addDamageEffect() {
  // 被ダメージに応じてラベルなど表示
  bool isDead = false;
  bool isShield = false;
  int sumDamage = 0;
  std::queue<DamageInfo>* queue = _characterManager->getDamageInfoQueue();
  while (!queue->empty()) { // キューが空になるまで取り出す
    DamageInfo info = queue->front();
    queue->pop();
    int damage = info.damage;
    DamageType damageType = info.damageType;
    // 被ダメージ表示しちゃう
    CCLabelAtlas* damageLabel = CCLabelAtlas::create(boost::lexical_cast<string>(damage).c_str(),
                                                     FileUtils::getFilePath("Image/damage_number.png").c_str(), 50, 100, '0');
    CCDirector* director = CCDirector::sharedDirector();
    damageLabel->setPosition(ccp(director->getWinSize().width / 2, 90));
    this->addChild(damageLabel);
    damageLabel->setScale(0);
    damageLabel->runAction(CCSequence::create(CCScaleTo::create(0.1, 0.8),
                                              CCDelayTime::create(0.5),
                                              CCScaleTo::create(0.2, 0.0),
                                              CCRemoveFromParentAction::create(),
                                              NULL));
    sumDamage += damage;
    if (damageType == DamageTypeDeath) {
      isDead = true;
    } else if (damageType == DamageTypeShield) {
      isShield = true;
      _characterManager->setShield(false);
      break;
    }
  }
  // 総ダメージに応じて画面を揺らしてやる
  
  if (sumDamage > 0) {
    // 画面点滅させて音を鳴らす
    SEManager::sharedManager()->registerEffect(FileUtils::getFilePath("SE/damage.mp3").c_str());
    BlinkLayer* bLayer = new BlinkLayer(ccc4(255, 0, 0, 255));
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
  }
  if (isDead) { // 死んだとき
    this->onGameOver();
  } else if (isShield) { // 盾装備してたとき
    SEManager::sharedManager()->registerEffect(FileUtils::getFilePath("SE/guard.mp3").c_str());
  }
}

void MainScene::changeMap(Map* nextMap) {
  if (_map) {
    // 前の背景画像削除
    if (_map->getBackground()) {
      this->removeChild(_map->getBackground(), true);
    }
    _map->release();
  }
  nextMap->retain();
  _map = nextMap;
  _level = nextMap->createInitialLevel(_characterManager); // レベルを生成する
  _enemyManager->setLevel(_level); // レベルをセット
  _enemyManager->removeAllEnemies();
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
  _skin->getController()->setEnable(false);
  _musicManager->pushIntroTracks();
  _characterManager->setRepeatCount(0); // repeatCountをリセット
  this->updateGUI();
}

void MainScene::changeSkin(Skin *newSkin, bool crossFade) {
  // スキンの切り替え
  // 後始末
  const float kCrossFadeSpeed = 1.0f;
  if (_skin != NULL) {
    newSkin->setController(_skin->getController()); // 古いコントローラーを受け渡す
    _skin->getController()->updateSkills(_characterManager, _level); // スキン更新
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
}

void MainScene::startBossBattle() {
  _skin->getController()->setEnable(false);
  _state = VCStateIntro; // イントロに移行
  this->changeMusic(_map->getCurrentMusic(_level), false);
  _characterManager->setRepeatCount(0);
  _skin->getController()->setEnable(false);
  _musicManager->pushIntroTracks();
}

void MainScene::gotoNextStage() {
  if (_state == VCStateFinish) {
    CCArray* maps = _map->getNextMaps();
    CCAssert(maps->count() > 0, "Next Map must be larger than 0.");
    if (maps->count() == 1) {
      this->changeMap((Map*)maps->objectAtIndex(0));
    } else if (maps->count() >= 2) {
      _mapSelector = MapSelector::create();
      _mapSelector->retain();
      _mapSelector->setNextMaps(maps);
      _skin->getController()->setEnable(false);
      this->addChild(_mapSelector, MainSceneZOrderUI);
      _state = VCStateMapSelect;
    }
  }
}

void MainScene::onFinishTracksCompleted() {
  if (_state == VCStateQTEFinish) { // QTEFinishのとき
    // おそらくボス撃破後なので、エンディングに移行します
    string endingScript = _map->getEndingName();
    CCAssert(endingScript.length() != 0, "Ending Script is not defined.");
    _musicManager->getMusic()->stop();
    EndingScene* endingLayer = new EndingScene(endingScript.c_str());
    endingLayer->autorelease();
    CCScene* ending = CCScene::create();
    ending->addChild(endingLayer);
    CCTransitionFade* fade = CCTransitionFade::create(5.0f, ending, ccc3(255, 255, 255));
    CCDirector::sharedDirector()->replaceScene(fade);
  } else if (_map->isBossStage() && _level->getLevel() == _map->getMaxLevel()) { // ボスステージで、現在が最高レベルの時
    // ボス戦を開始します
    this->startBossBattle();
  } else if (_level->getLevel() >= _map->getMaxLevel() + 1 && _map->getNextMaps()->count() > 0) { // 最高レベルの次の時で、次のマップが存在するとき
    // 次のステージに移動します
    this->gotoNextStage();
  }
}

void MainScene::setPause(bool pause) {
  CCScheduler* scheduler = CCDirector::sharedDirector()->getScheduler();
  if (pause && _pausedTargets == NULL) {
    PauseLayer* layer = new PauseLayer(this);
    layer->autorelease();
    _pausedTargets = scheduler->pauseAllTargets();
    _pausedTargets->retain();
    _musicManager->getMusic()->pause();
    this->addChild(layer, 1000, PAUSE_LAYER_TAG);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/pause.mp3").c_str());
  } else {
    _musicManager->getMusic()->play();
    scheduler->resumeTargets(_pausedTargets);
    _pausedTargets = NULL;
    this->removeChildByTag(PAUSE_LAYER_TAG, true);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/cancel.mp3").c_str());
  }
}

void MainScene::changeMusic(MusicSet* mSet, bool enablePreload) {
  _musicManager->setMusicSet(mSet); // 音楽セットを切り替える
  if (enablePreload) {
    _musicManager->preloadAllTracks(_characterManager, _level); // 曲データを読む
  }
  // 作曲者情報と曲名を表示する
  CCNode* musicInfo = CCNode::create();
  CCLabelTTF* nameShadowLabel = CCLabelTTF::create(mSet->getName().c_str(),
                                                   "Helvetica",
                                                   24,
                                                   CCSizeMake(200, 30),
                                                   kCCTextAlignmentRight);
  musicInfo->addChild(nameShadowLabel);
  nameShadowLabel->setColor(ccc3(33, 33, 33));
  nameShadowLabel->setPosition(ccp(3, -3));
  CCLabelTTF* composerShadowLabel = CCLabelTTF::create(mSet->getComposer().c_str(),
                                                       "Helvetica",
                                                       16,
                                                       CCSizeMake(200, 20),
                                                       kCCTextAlignmentRight);
  composerShadowLabel->setColor(ccc3(33, 33, 33));
  composerShadowLabel->setPosition(ccp(3, -28));
  musicInfo->addChild(composerShadowLabel);
  CCLabelTTF* nameLabel = CCLabelTTF::create(mSet->getName().c_str(),
                                             "Helvetica",
                                             24,
                                             CCSizeMake(200, 30),
                                             kCCTextAlignmentRight);
  musicInfo->addChild(nameLabel);
  CCLabelTTF* composerLabel = CCLabelTTF::create(mSet->getComposer().c_str(),
                                                 "Helvetica",
                                                 16,
                                                 CCSizeMake(200, 20),
                                                 kCCTextAlignmentRight);
  composerLabel->setPosition(ccp(0, -25));
  musicInfo->addChild(composerLabel);
  this->addChild(musicInfo, MainSceneZOrderUI);
  musicInfo->setPosition(ccp(600, 40));
  musicInfo->runAction(CCSequence::create(CCMoveTo::create(0.5f, ccp(360, 40)),
                                          CCDelayTime::create(2.0f),
                                          CCMoveTo::create(0.5f, ccp(600, 40)),
                                          CCRemoveFromParentAction::create(),
                                          NULL));
}

VCState MainScene::getState () {
  return _state;
}