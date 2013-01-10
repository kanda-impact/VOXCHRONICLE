//
//  MainScene.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/8/28.
//
//

#include <sstream>
#include <cstdlib>
#include <boost/random.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>

#include "MainScene.h"
#include "Enemy.h"
#include "MapSelector.h"
#include "TrackCache.h"
#include "LuaObject.h"
#include "FileUtils.h"
#include "BlinkLayer.h"
#include "TitleScene.h"

using namespace std;
using namespace cocos2d;
using namespace VISS;

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
  _music = new Music(3);
  _music->setTrackDidBackFunction(boost::bind(&MainScene::trackDidBack, this, _1, _2, _3));
  _music->setTrackDidFinishFunction(boost::bind(&MainScene::trackDidFinishPlaying, this, _1, _2, _3, _4));
  _music->setTrackWillFinishFunction(boost::bind(&MainScene::trackWillFinishPlaying, this, _1, _2, _3, _4));
  
  _currentSkillInfo.skillTrackName = "";
  _currentSkillInfo.type = SkillPerformTypeNone;
  _currentSkillInfo.skill = NULL;
  
  _turnCount = 0;
  _mapTurnCount = 0;
  _introCount = 0;
  _finishCount = 0;
  
  LuaObject* setting = new LuaObject("Script/setting", "Setting");
  setting->autorelease();
  
  CCDirector* director = CCDirector::sharedDirector();
  
  // 背景の追加
  // 将来的にはSkinクラスを実装して、スキンによって背景を変更するようにしたいが
  // 今はとりあえずここにSpriteをおいておきます
  CCSprite* background = CCSprite::create(FileUtils::getFilePath("floor0.png").c_str());
  CCAnimation* animation = CCAnimation::create();
  animation->addSpriteFrame(CCSpriteFrame::create(FileUtils::getFilePath("floor0.png").c_str(), CCRectMake(0, 0, 480, 122.5)));
  animation->addSpriteFrame(CCSpriteFrame::create(FileUtils::getFilePath("floor1.png").c_str(), CCRectMake(0, 0, 480, 122.5)));
  animation->addSpriteFrame(CCSpriteFrame::create(FileUtils::getFilePath("floor2.png").c_str(), CCRectMake(0, 0, 480, 122.5)));
  animation->setLoops(-1);
  animation->setDelayPerUnit(10.0 / 60.0);
  background->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
  
  CCPoint center = ccp(director->getWinSize().width / 2.0f, 122.5 / 2.0f);
  background->setPosition(center);
  this->addChild(background);
  
  _enemyManager = EnemyManager::create();
  _enemyManager->retain();
  this->addChild(_enemyManager);
  
  _focus = CCSprite::create(FileUtils::getFilePath("focus.png").c_str());
  _focus->retain();
  _focus->setVisible(false);
  _focus->setAnchorPoint(ccp(0.5f, 0.0f));
  this->addChild(_focus);
  
  _controller = Controller::create();
  _controller->retain();
  _characterManager = new CharacterManager();
  _characterManager->retain();
  CCSize size = director->getWinSize();
  this->addChild(_controller);
  _characterManager->setLevel(setting->getInt("initialLevel"));
  
  map->retain();
  _map = map;
  _level = _map->createInitialLevel();
  _enemyManager->setLevel(_level);
  
  _musicSet = _map->getCurrentMusic(_level);
  _musicSet->preloadAllTracks();
  
  TrackCache::sharedCache()->addTrack(FileUtils::getFilePath("Music/general/select_stage.wav"), 0);
  
  _state = VCStateIntro;
  
  _messageWindow = new MessageWindow(FONT_NAME, 64);
  _messageWindow->retain();
  _messageWindow->setPosition(ccp(100, 100));
  
  _mapSelector = NULL;
  
  this->addChild(_messageWindow);
  
  this->scheduleUpdate();
  _preLevel = _level->getLevel();
  
  _statusLayer = new StatusLayer();
  _statusLayer->retain();
  
  this->addChild(_statusLayer);
  this->updateGUI();
  _controller->updateSkills(_characterManager);
  
  _qteTrigger = NULL;
  
  return true;
}

MainScene::~MainScene() {
  delete _music;
  _map->release();
  _messageWindow->release();
  _controller->release();
  _enemyManager->release();
  _characterManager->release();
  _statusLayer->release();
  _focus->release();
  _musicSet->release();
  if (_mapSelector != NULL) {
    _mapSelector->release();
  }
}

void MainScene::update(float dt) {
  if (_state == VCStateMain) {
    _controller->setEnable(!_characterManager->isPerforming());
    if (_characterManager->getHP() <= 0) {
      this->onGameOver();
    }
  }
}

void MainScene::onEnterTransitionDidFinish() {
  this->pushIntroTracks();
  _music->play();
  _statusLayer->setMarkerDuration(_music->getTrack(0)->getDuration() / 4.0f);
}

void MainScene::trackDidBack(Music *music, Track *currentTrack, int trackNumber) {
  if (_state == VCStateMain) {
    _enemyManager->nextTurn(_characterManager);
    CCObject* obj = NULL;
    CCARRAY_FOREACH(_enemyManager->getEnemies(), obj) {
      Enemy* enemy = (Enemy*)obj;
      if (enemy->getRow() == 0) {
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
    ++_introCount;
  } else {
    _introCount = 0;
  }
  if (_state == VCStateFinish || _state == VCStateQTEFinishStart || _state == VCStateQTEFinish) {
    ++_finishCount;
  } else {
    _finishCount = 0;
  }
  if (_state == VCStateIntro) {
    int maxIntroCount = _musicSet->getIntroCount();
    if (_introCount == maxIntroCount - 1) { // イントロが終わったとき
      _controller->setEnable(true);
      _state = VCStateMain;
    }
  } else if (_state == VCStateFinish || _state == VCStateQTEFinish) {
    this->onFinishTracksCompleted();
  } else if (_state == VCStateQTEFinishStart) { // 寸止めQTE UI追加
    _qteTrigger = new QTETrigger(_enemyManager);
    _state = VCStateQTE;
    this->addChild(_qteTrigger);
  } else if (_state == VCStateQTE) {
    if (_qteTrigger != NULL && _qteTrigger->isButtonPressed()) {
      _state = VCStateQTEFinish;
      _finishCount = _musicSet->getFinishCount() - 3;
      for (int i = 2; i < _musicSet->getFinishCount(); ++i) {
        stringstream finish;
        finish << "finish" << i << ".m4a";
        _music->pushTrack(_musicSet->getPrefixedMusicName(finish.str().c_str()).c_str(), 0);
        _music->pushTrack(_musicSet->getPrefixedMusicName("silent.m4a").c_str(), 1);
        _music->pushTrack(_musicSet->getPrefixedMusicName("silent.m4a").c_str(), 2);
      }
    } else {
      _music->pushTrack(_musicSet->getPrefixedMusicName("silent.m4a").c_str(), 0);
      _music->pushTrack(_musicSet->getPrefixedMusicName("silent.m4a").c_str(), 1);
      _music->pushTrack(_musicSet->getPrefixedMusicName("silent.m4a").c_str(), 2);
    }
  } else if (_state == VCStateMain) {
    
    // リフの設定
    Enemy* nearest = _enemyManager->getNearestEnemy();
    if (nearest) {
      stringstream ss;
      ss << "counter" << nearest->getCounter() << ".m4a";
      string file(_musicSet->getPrefixedMusicName(ss.str().c_str()));
      Track* track = music->pushTrack(file.c_str(), 1);
      
      int row = nearest->getRow();
      int denominator = (MAX_ROW + 1) * MAX_ROW / 2.0;
      int numerator = ((MAX_ROW - row) + 1) * (MAX_ROW - row) / 2.0;
      float volume = 0.5 + 1.0 * numerator / denominator;
      track->setVolume(volume);
    } else {
      string file(_musicSet->getPrefixedMusicName("counter0.m4a"));
      Track* track = music->pushTrack(file.c_str(), 1);
      track->setVolume(0);
    }
    
    // ドラムの設定
    stringstream drumFileStream;
    int drumLevel = this->calcDrumScore();
    if (drumLevel == 0) {
      drumFileStream << "silent.m4a";
    } else {
      drumFileStream << "drum" << drumLevel - 1 << ".m4a";
    }
    Track* track = music->pushTrack(_musicSet->getPrefixedMusicName(drumFileStream.str().c_str()).c_str(), 2);
    track->setVolume(0.7);
    
    // メロディの設定
    Skill* skill = NULL;
    if (_characterManager->isPerforming()) {
      skill = _characterManager->getCurrentSkill();
    } else {
      skill = _controller->currentTriggerSkill();
    }
    SkillPerformType performType = SkillPerformTypeNone;
    string name = _characterManager->checkSkillTrackName(skill, performType, _musicSet);
    _currentSkillInfo.skillTrackName = name;
    _currentSkillInfo.type = performType;
    _currentSkillInfo.skill = skill;
    string file(_musicSet->getPrefixedMusicName((name + ".m4a").c_str()));
    string trackName(file);
    music->pushTrack(file.c_str(), 0);
    
    // QTE開始
    if (_enemyManager->getBoss() != NULL && _enemyManager->getBoss()->getHP() <= 0) { // 寸止めQTE開始
      _state = VCStateQTEFinishStart;
      for (int i = 0; i < _musicSet->getFinishCount() - 2; ++i) {
        stringstream finish;
        finish << "finish" << i << ".m4a";
        _music->pushTrack(_musicSet->getPrefixedMusicName(finish.str().c_str()).c_str(), 0);
        _music->pushTrack(_musicSet->getPrefixedMusicName("silent.m4a").c_str(), 1);
        _music->pushTrack(_musicSet->getPrefixedMusicName("silent.m4a").c_str(), 2);
      }
    }
  }
  this->updateGUI(); // GUI更新
}

void MainScene::trackDidFinishPlaying(Music *music, Track *finishedTrack, Track *nextTrack, int trackNumber) {
  
  // メインの動きを実行
  Skill* skill = _currentSkillInfo.skill;
  SkillPerformType performType = _currentSkillInfo.type;
  string name = _currentSkillInfo.skillTrackName;
  
  bool isHit = true; // ヒットしたかどうか
  /* 以下のとき、ヒットしていない
   1. 対象が自分以外の技を使用し、対象の全てについて
   ・盾やバリアに弾かれた
   　　　　　　 ・盾やバリアを破壊した場合、与ダメージが0でもヒットした扱いにする
   ・本来、ダメージを与えられる技を使ったはずなのに被ダメージが0である
   　　　　　   ・例えばノックバックはダメージが0でも、本来与えるダメージが0なのでヒットしている
   ・本来ダメージが与えられるはずなのに、耐性やレベル補正でダメージが0だった場合、ヒットしていない
   */
  if (skill && performType == SkillPerformTypeSuccess) {

    int preExp = _characterManager->getExp();
    CCDictionary* info = _enemyManager->performSkill(skill, _characterManager); // ここで経験値が貰える
    CCArray* enemies = (CCArray*)info->objectForKey("enemies");
    CCArray* damages = (CCArray*)info->objectForKey("damages");
    CCArray* damageTypes = (CCArray*)info->objectForKey("damageTypes");
    int enemyCount = enemies->count();
    for (int i = 0; i < enemyCount; ++i) {
      isHit = true;
      Enemy* enemy = (Enemy*)enemies->objectAtIndex(i);
      CCLabelAtlas* damageLabel = CCLabelAtlas::create(boost::lexical_cast<string>(((CCInteger*)damages->objectAtIndex(i))->getValue()).c_str(),
                                                       FileUtils::getFilePath("damage_number.png").c_str(), 50, 100, '0');
      // ダメージが0かつ、元々ダメージのない技じゃないかつ、アイテムも破壊していないとき、ヒットしていない状態にしてやる
      int damage = ((CCInteger*)damages->objectAtIndex(i))->getValue();
      DamageType damageType = (DamageType)((CCInteger*)damageTypes->objectAtIndex(i))->getValue();
      if (damage == 0 && damageType != DamageTypeBarrierBreak && damageType != DamageTypeShieldBreak && damageType != DamageTypeNoDamage) {
        isHit = false;
      }
      damageLabel->setPosition(enemy->getPosition());
      float scale = enemy->getCurrentScale(enemy->getRow());
      damageLabel->setScale(scale);
      this->addChild(damageLabel);
      damageLabel->runAction(CCSequence::create(CCFadeIn::create(0.2),
                                                CCDelayTime::create(0.5),
                                                CCFadeOut::create(0.2),
                                                CCCallFuncN::create(damageLabel, callfuncN_selector(MainScene::removeNode)),
                                                NULL));
    }
    
    // カットインを追加する
    string cutinFile = string(skill->getIdentifier()) + "_icon.png";
    CCSprite* cutin = CCSprite::create(cutinFile.c_str());
    if (cutin != NULL) {
      const int height = 100;
      cutin->setPosition(ccp(0, height));
      float duration = _music->getCurrentMainTrack()->getDuration();
      CCSize size = CCDirector::sharedDirector()->getWinSize();
      if (isHit) {
        // 成功したとき、カットインを挿入
        cutin->runAction(CCSequence::create(CCMoveTo::create(duration * 0.125, ccp(size.width / 2.0, height)),
                                            CCDelayTime::create(duration * 0.25),
                                            CCMoveTo::create(duration * 0.125, ccp(size.width, height)),
                                            CCCallFuncN::create(this, callfuncN_selector(MainScene::removeNode)),
                                            NULL));
      } else {
        // ミスったとき、コマンドを落とす
        cutin->runAction(CCSequence::create(CCMoveTo::create(duration * 0.125, ccp(size.width / 2.0, height)),
                                            CCRotateBy::create(duration * 0.125, 45),
                                            CCDelayTime::create(duration * 0.125),
                                            CCMoveTo::create(duration * 0.125, ccp(size.width / 2.0, -100)),
                                            CCCallFuncN::create(this, callfuncN_selector(MainScene::removeNode)),
                                            NULL));
      }
      this->addChild(cutin);
      
    }
    
    if (isHit) {
      // ヒットしたとき、SEがあればSEをならしてやる
      if (enemies->count() > 0) { // 対象が1体以上いるとき
        DamageType damageType = (DamageType)((CCInteger*)damageTypes->objectAtIndex(0))->getValue();
        stringstream seStream;
        // 今は当たった敵1体目のダメージタイプをとってきてならしているが、
        // 複数体に同時に当たったときは遅延して順番にならしても良さそう
        if (damageType == DamageTypeShieldBreak) {
          seStream << "shield_break.mp3";
        } else if (damageType == DamageTypeBarrierBreak) {
          seStream << "barrier_break.mp3";
        } else if (skill->hasSE()) {
          // 対象が自分、もしくは対象が1体以上いたとき、ダメージ効果音をならします
          seStream << "SE/"<< skill->getIdentifier() << "_effect.mp3";
        }
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath(seStream.str().c_str()).c_str());
      }  else if (skill->getRange() == SkillRangeSelf && skill->hasSE()) { // 対象が自分だけ、かつSEを持っているとき
        stringstream seStream;
        // 効果音をならします
        seStream << "SE/"<< skill->getIdentifier() << "_effect.mp3";
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath(seStream.str().c_str()).c_str());
      }
    } else if (!isHit) { // ヒットしていないとき、強制的にミス音にする
      name = "miss"; // 差し替えたので今は強制的にミス音にできない。後で考える
      if (enemyCount == 0) {
        // 誰もいないときピロリ音
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("miss.m4a").c_str());
      } else {
        DamageType damageType = (DamageType)((CCInteger*)damageTypes->objectAtIndex(0))->getValue();
        if (damageType == DamageTypePhysicalInvalid) {
          // 1体だけ敵がいるのに当たらず、盾持ちだったとき
          CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("shield_invalid.mp3").c_str());
        } else if (damageType == DamageTypeMagicalInvalid) {
          // バリア持ちだったとき
          CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("barrier_invalid.mp3").c_str());
        }
      }
      
    }
    int getExp = ((CCInteger*)info->objectForKey("exp"))->getValue();
    CCArray* fixed = _map->getFixedEnemies(preExp, preExp + getExp);
    if (fixed->count() > 0) {
      _enemyManager->pushEnemiesQueue(fixed);
    }
    this->checkLevelUp();
  } else if (performType == SkillPerformTypeNone) {
    // 何も実行しなかったとき
    // MP回復 コマンド化したのでコメントアウトしておきます
    //_characterManager->addMP(1);
  }
  
  _controller->updateSkills(_characterManager);
  this->updateFocus();
  _currentSkillInfo.skillTrackName = "";
  _currentSkillInfo.type = SkillPerformTypeNone;
  _currentSkillInfo.skill = NULL;
  
  // ターンカウントを進める
  ++_turnCount;
  ++_mapTurnCount;
  // このターンにテンション使ってないときreset
  if (_characterManager->getLastSkill() != NULL && strcmp(_characterManager->getLastSkill()->getIdentifier(), "tension")) {
    _characterManager->resetTension();
  }
  if (!_characterManager->isPerforming()) {
    _controller->resetAllTriggers();
    _enemyManager->purgeAllTrash();
  }
  /*if (_state == VCStateMain) {
   if (_enemyManager->getBoss() != NULL && _enemyManager->getBoss()->getHP() == 0) {
   _controller->setEnable(false);
   _qteTrigger = new QTETrigger(_enemyManager);
   _qteTrigger->retain();
   this->addChild(_qteTrigger);
   _state = VCStateBoss;
   CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/qte.mp3").c_str());
   }
   }*/
}

void MainScene::updateGUI() {
  _statusLayer->setCurrentHP(_characterManager->getHP());
  _statusLayer->setMaxHP(_characterManager->getMaxHP());
  _statusLayer->setCurrentMP(_characterManager->getMP());
  _statusLayer->setMaxMP(_characterManager->getMaxMP());
  _statusLayer->setLevel(_characterManager->getLevel());
}

void MainScene::pushIntroTracks() {
  _controller->setEnable(false);
  string main, counter, drum;
  _music->removeAllNextTracks(); // 次以降の曲を強制的に削除
  int introCount = _musicSet->getIntroCount();
  _introCount = 0;
  if (introCount == 0) {
    // イントロなしのとき、いきなり曲を鳴らします
    main = _musicSet->getPrefixedMusicName("wait0.m4a");
    counter= _musicSet->getPrefixedMusicName("counter0.m4a");
    drum = _musicSet->getPrefixedMusicName("drum0.m4a");
    _music->pushTrack(main.c_str(), 0);
    _music->pushTrack(counter.c_str(), 1);
    _music->pushTrack(drum.c_str(), 2);
  } else {
    // イントロありのとき、イントロの数だけpushします
    int maxIntroCount = _musicSet->getIntroCount();
    for (int i = 0 ; i < maxIntroCount; ++i) {
      stringstream intro;
      intro << "intro" << i << ".m4a";
      _music->pushTrack(_musicSet->getPrefixedMusicName(intro.str().c_str()).c_str(), 0);
      _music->pushTrack(_musicSet->getPrefixedMusicName("silent.m4a").c_str(), 1);
      _music->pushTrack(_musicSet->getPrefixedMusicName("silent.m4a").c_str(), 2);
    }
  }
  _music->getTrack(1)->setVolume(0);
  _music->getTrack(2)->setVolume(0.7);
}

void MainScene::pushFinishTracks() {
  _controller->setEnable(false);
  int maxFinishCount = _musicSet->getFinishCount();
  
  _music->removeAllNextTracks(); // 次以降の曲を強制的に削除
  _finishCount = 0;
  if (maxFinishCount == 0) {
    this->onFinishTracksCompleted();
  } else {
    // フィニッシュ曲をpushしまくる
    for (int i = 0 ; i < maxFinishCount; ++i) {
      stringstream finish;
      finish << "finish" << i << ".m4a";
      _music->pushTrack(_musicSet->getPrefixedMusicName(finish.str().c_str()).c_str(), 0);
      _music->pushTrack(_musicSet->getPrefixedMusicName("silent.m4a").c_str(), 1);
      _music->pushTrack(_musicSet->getPrefixedMusicName("silent.m4a").c_str(), 2);
    }
  }
}

bool MainScene::checkLevelUp() {
  int currentLevel = _characterManager->getLevel();
  if (currentLevel != _preLevel) { // レベルが上がったとき
    _introCount = 0;
    _preLevel = currentLevel;
    _map->performOnLevel(currentLevel, _characterManager, _enemyManager); // スクリプトを呼んでやる
    _characterManager->updateParameters();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/levelup.mp3").c_str());
    _level = _map->createLevel(currentLevel);
    
    _enemyManager->setLevel(_level);
    _enemyManager->removeAllEnemiesQueue();
    this->updateGUI();
    if (_level->getLevel() == _map->getMaxLevel() && _map->isBossStage()) { // 最高レベルのとき、かつボス面のとき
      // 道中フィニッシュ曲を流す。フィニッシュ曲が終わったらボス面に切り替えてイントロ曲を流す
      _state = VCStateFinish;
      _controller->setEnable(false);
      this->pushFinishTracks();
    } else if (_level->getLevel() >= _map->getMaxLevel() + 1) {
      _state = VCStateFinish;
      _controller->setEnable(false);
      this->pushFinishTracks();
    }
    return true;
  }
  return false;
}

void MainScene::addGameOverButtons() {
  CCLabelTTF* replayLabel = CCLabelTTF::create("リプレイ", "", 24);
  CCLabelTTF* titleLabel = CCLabelTTF::create("タイトル", FONT_NAME, 24);
  CCMenu* menu = CCMenu::create(CCMenuItemLabel::create(replayLabel, this, menu_selector(MainScene::replayButtonPressed)),
                                CCMenuItemLabel::create(titleLabel, this, menu_selector(MainScene::titleButtonPressed)),
                                NULL);
  CCDirector* director = CCDirector::sharedDirector();
  menu->setPosition(ccp(director->getWinSize().width / 2, 90));
  menu->alignItemsVerticallyWithPadding(20);
  this->addChild(menu);
}

void MainScene::replayButtonPressed(CCObject *sender) {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/decide.mp3").c_str());
  CCScene* scene = CCScene::create();
  scene->addChild(MainScene::create());
  CCTransitionFade* transition = CCTransitionFade::create(0.5, scene);
  CCDirector::sharedDirector()->replaceScene(transition);
}

void MainScene::titleButtonPressed(CCObject *sender) {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/decide.mp3").c_str());
  CCScene* scene = CCScene::create();
  scene->addChild(TitleScene::create());
  CCTransitionFade* transition = CCTransitionFade::create(0.5, scene);
  CCDirector::sharedDirector()->replaceScene(transition);
}

void MainScene::onGameOver() {
  _state = VCStateGameOver;
  CCLabelTTF* gameOverLabel = CCLabelTTF::create("GAME OVER", FONT_NAME, 48);
  CCDirector* director = CCDirector::sharedDirector();
  CCPoint center = CCPointMake(director->getWinSize().width / 2, director->getWinSize().height / 2);
  CCLabelTTF* gameOverShadowLavel = CCLabelTTF::create("GAME OVER", FONT_NAME, 48);
  gameOverShadowLavel->setColor(ccc3(64, 64, 64));
  gameOverShadowLavel->setPosition(center);
  gameOverLabel->setPosition(ccpAdd(ccp(gameOverShadowLavel->getContentSize().width / 2, gameOverShadowLavel->getContentSize().height / 2), ccp(-3, 3)));
  this->addChild(gameOverShadowLavel);
  gameOverShadowLavel->addChild(gameOverLabel);
  gameOverShadowLavel->runAction(CCSequence::create(CCDelayTime::create(3.0),
                                                    CCMoveTo::create(0.1, ccp(director->getWinSize().width / 2, 200)),
                                                    CCCallFunc::create(this, callfunc_selector(MainScene::addGameOverButtons)),
                                                    NULL));
  _music->stop();
  _controller->setVisible(false);
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("Music/general/gameover.mp3").c_str());
}

void MainScene::removeNode(CCNode* node) {
  this->removeChild(node, true);
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

int MainScene::calcDrumScore () {
  // KYDS
  int score = 0;
  // 敵の数によって分岐
  if (_enemyManager->getEnemies()) {
    int count = _enemyManager->getEnemies()->count();
    if (count == 2 || count == 3) {
      score += 1;
    } else if (count == 4 || count == 5) {
      score += 2;
    } else if (count >= 6) {
      score += 3;
    }
  }
  Enemy* nearest = _enemyManager->getNearestEnemy();
  if (nearest) {
    int row = nearest->getRow();
    if (row <= 1) {
      score += 2;
    } else if (row <= 4) {
      score += 1;
    } else {
      score += 0;
    }
  }
  int tension = _characterManager->getTension();
  score += tension;
  return min(score, 4);
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
                                                     FileUtils::getFilePath("damage_number.png").c_str(), 50, 100, '0');
    CCDirector* director = CCDirector::sharedDirector();
    damageLabel->setPosition(ccp(director->getWinSize().width / 2, 90));
    this->addChild(damageLabel);
    damageLabel->setScale(0);
    damageLabel->runAction(CCSequence::create(CCScaleTo::create(0.1, 0.8),
                                              CCDelayTime::create(0.5),
                                              CCScaleTo::create(0.2, 0.0),
                                              CCCallFuncN::create(damageLabel, callfuncN_selector(MainScene::removeNode)),
                                              NULL));
    sumDamage += damage;
    if (damageType == DamageTypeDeath) {
      isDead = true;
    } else if (damageType == DamageTypeShield) {
      isShield = true;
      break;
    }
  }
  // 総ダメージに応じて画面を揺らしてやる
  
  if (sumDamage > 0) {
    // 画面点滅させて音を鳴らす
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/damage.mp3").c_str());
    BlinkLayer* bLayer = new BlinkLayer(ccc4(255, 0, 0, 255));
    bLayer->autorelease();
    this->addChild(bLayer);
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
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/guard.mp3").c_str());
  }
}

void MainScene::changeMap(Map* nextMap) {
  _map->release();
  nextMap->retain();
  _map = nextMap;
  _level = nextMap->createInitialLevel(); // レベルを生成する
  _enemyManager->setLevel(_level); // レベルをセット
  _enemyManager->removeAllEnemiesQueue(); // キューを初期化
  //this->removeChild(_mapSelector, true);
  //_mapSelector->release();
  //_mapSelector = NULL;
  _mapTurnCount = 0; // マップカウント0に戻す
  _state = VCStateIntro;
  _musicSet = _map->getCurrentMusic(_level); // 音楽セットを切り替える
  TrackCache::sharedCache()->purgeAllTracks(); // キャッシュを削除する
  //_musicSet->preloadAllTracks();
  _introCount = 0;
  _finishCount = 0;
  this->pushIntroTracks();
  this->updateGUI();
}

void MainScene::startBossBattle() {
  _controller->setEnable(false);
  _state = VCStateIntro; // イントロに以降
  _musicSet = _map->getCurrentMusic(_level); // 音楽セットを切り替える
  TrackCache::sharedCache()->purgeAllTracks(); // キャッシュを削除する
  //_musicSet->preloadAllTracks();
  this->pushIntroTracks();
}

void MainScene::gotoNextStage() {
  // マップセレクターは後で実装します
  CCArray* maps = _map->getNextMaps();
  this->changeMap((Map*)maps->lastObject()); // マップを強制的に切り替える
}

void MainScene::onFinishTracksCompleted() {
  int maxFinishCount = _musicSet->getFinishCount();
  if (_finishCount == maxFinishCount) { // フィニッシュ曲が終わったとき
    if (_state == VCStateQTEFinish) { // QTEフィニッシュ後
      _enemyManager->removeEnemy(_enemyManager->getBoss());
      _enemyManager->setBoss(NULL);
      _characterManager->setLevel(_characterManager->getLevel() + 1);
      _state = VCStateMain;
      this->gotoNextStage();
    } else if (_map->isBossStage() && _level->getLevel() == _map->getMaxLevel()) { // ボスステージで、現在が最高レベルの時
      this->startBossBattle();
    } else if (_level->getLevel() == _map->getMaxLevel() + 1 && _map->getNextMaps() > 0) { // 最高レベルの次の時で、次のマップが存在するとき
      this->gotoNextStage();
    }
  }
}
