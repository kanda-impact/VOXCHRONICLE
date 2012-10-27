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

using namespace std;
using namespace cocos2d;
using namespace VISS;

bool MainScene::init() {
  if ( !CCLayer::init() ) {
    return false;
  }
  _music = new Music(3);
  _music->setTrackDidBackFunction(boost::bind(&MainScene::trackDidBack, this, _1, _2, _3));
  _music->setTrackDidFinishFunction(boost::bind(&MainScene::trackDidFinishPlaying, this, _1, _2, _3, _4));
  _music->setTrackWillFinishFunction(boost::bind(&MainScene::trackWillFinishPlaying, this, _1, _2, _3, _4));
  
  _turnCount = 0;
  _mapTurnCount = 0;
  
  LuaObject* setting = new LuaObject("Script/setting", "Setting");
  setting->autorelease();
  
  _enemyManager = EnemyManager::create();
  _enemyManager->retain();
  this->addChild(_enemyManager);
  
  CCDirector* director = CCDirector::sharedDirector();
  _controller = Controller::create();
  _controller->retain();
  _characterManager = new CharacterManager();
  _characterManager->retain();
  CCSize size = director->getWinSize();
  this->addChild(_controller);
  _characterManager->setLevel(setting->getInt("initialLevel"));
  _controller->updateSkills(_characterManager);
  
  _map = new Map(setting->getString("initialMap"));
  _level = _map->createInitialLevel();
  _enemyManager->setLevel(_level);
  
  _levelLabel = CCLabelTTF::create("", "Helvetica", 16);
  _levelLabel->setPosition(CCPointMake(40, 280));
  _hpLabel = CCLabelTTF::create("", "Helvetica", 16);
  _hpLabel->setPosition(CCPointMake(400, 290));
  _mpLabel = CCLabelTTF::create("", "Helvetica", 16);
  _mpLabel->setPosition(CCPointMake(400, 270));
  _expLabel = CCLabelTTF::create("", "Helvetica", 16);
  _expLabel->setPosition(CCPointMake(40, 260));
  _nextExpLabel = CCLabelTTF::create("", "Helvetica", 16);
  _nextExpLabel->setPosition(CCPointMake(40, 240));
  _mapLabel = CCLabelTTF::create("", "Helvetica", 16);
  _mapLabel->setPosition(CCPointMake(60, 220));
  this->addChild(_levelLabel);
  this->addChild(_hpLabel);
  this->addChild(_mpLabel);
  this->addChild(_expLabel);
  this->addChild(_nextExpLabel);
  this->addChild(_mapLabel);
  
  TrackCache::sharedCache()->addTrack(FileUtils::getFilePath("Music/select/select_stage.wav"));
  
  this->pushInitialTracks(_map);
  
  _state = VCStateIntro;
  
  this->updateGUI();
  
  _messageWindow = new MessageWindow("Helvetica", 64);
  _messageWindow->retain();
  _messageWindow->setPosition(ccp(100, 100));
  
  this->addChild(_messageWindow);
  
  this->scheduleUpdate();
  _preLevel = _level->getLevel();
  return true;
}

MainScene::~MainScene() {
  delete _music;
  _messageWindow->release();
  _controller->release();
  _enemyManager->release();
  _characterManager->release();
  if (_mapSelector) {
    _mapSelector->release();
  }
}

void MainScene::update(float dt) {
  _controller->setEnable(!_characterManager->isPerforming());
}

void MainScene::onEnterTransitionDidFinish() {
  _music->play();
}

void MainScene::trackDidBack(Music *music, Track *currentTrack, int trackNumber) {
  if (trackNumber == 0 && _state == VCStateMain) {
    _enemyManager->lotPopEnemy();
    CCObject* obj = NULL;
    CCARRAY_FOREACH(_enemyManager->getEnemies(), obj) {
      Enemy* enemy = (Enemy*)obj;
      if (enemy->getRow() > 0) {
        if (enemy->canMove()) {
          enemy->moveRow(-1);
        }
      } else {
        int damage = round(enemy->getAttack() * _characterManager->getLevelOffsetRate(enemy->getLevel(), _characterManager->getLevel()));
        cout << damage << endl;
        DamageType result = _characterManager->damage(damage);
        if (result == DamageTypeDeath) {
          _state = VCStateGameOver;
          CCLabelTTF* gameOverLabel = CCLabelTTF::create("GAME OVER", "Helvetica", 48);
          CCDirector* director = CCDirector::sharedDirector();
          CCPoint center = CCPointMake(director->getWinSize().width / 2, director->getWinSize().height / 2);
          CCLabelTTF* gameOverShadowLavel = CCLabelTTF::create("GAME OVER", "Helvetica", 48);
          gameOverShadowLavel->setColor(ccc3(64, 64, 64));
          gameOverShadowLavel->setPosition(ccpAdd(center, CCPointMake(3, -3)));
          gameOverLabel->setPosition(center);
          this->addChild(gameOverShadowLavel);
          this->addChild(gameOverLabel);
          _music->stop();
          _controller->setVisible(false);
          CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/death.mp3").c_str());
        }
        _enemyManager->removeEnemy(enemy);
      }
    }
    this->updateGUI();
  }
}

void MainScene::trackWillFinishPlaying(Music *music, Track *currentTrack, Track *nextTrack, int trackNumber) {
  if (_state == VCStateIntro) {
    if (_mapTurnCount < _map->getIntroCount() - 1) {
      if (trackNumber == 0) {
        stringstream intro;
        intro << "intro" << _mapTurnCount + 1 << ".wav";
        _music->pushTrack(_map->getPrefixedMusicName(intro.str().c_str()).c_str(), 0);
        _music->pushTrack(_map->getPrefixedMusicName("silent.wav").c_str(), 1);
        _music->pushTrack(_map->getPrefixedMusicName("silent.wav").c_str(), 2);
      }
    } else {
      _state = VCStateMain;
      _music->pushTrack(_map->getPrefixedMusicName("wait.wav").c_str(), 0);
      _music->pushTrack(_map->getPrefixedMusicName("counter0.wav").c_str(), 1);
      _music->pushTrack(_map->getPrefixedMusicName("drum0.wav").c_str(), 2);
    }
  } else if (_state == VCStateMain) {
    if (trackNumber == 0) {
      Skill* skill = NULL;
      if (_characterManager->isPerforming()) {
        skill = _characterManager->getCurrentSkill();
      } else {
        skill = _controller->currentTriggerSkill();
      }
      std::stringstream ss;
      SkillPerformType performType = SkillPerformTypeNone;
      const char* name = _characterManager->checkSkillTrackName(skill, performType);
      ss << name << ".wav";
      string file(_map->getPrefixedMusicName(ss.str().c_str()));
      string trackName(name);
      _music->pushTrack(file.c_str(), 0);
      if (skill && performType == SkillPerformTypeSuccess) {
        int preExp = _characterManager->getExp();
        CCDictionary* info = _enemyManager->performSkill(skill, _characterManager); // ここで経験値が貰える
        CCArray* enemies = (CCArray*)info->objectForKey("enemies");
        CCArray* damages = (CCArray*)info->objectForKey("damages");
        for (int i = 0; i < enemies->count(); ++i) {
          Enemy* enemy = (Enemy*)enemies->objectAtIndex(i);
          CCLabelAtlas* damageLabel = CCLabelAtlas::create(boost::lexical_cast<string>(((CCInteger*)damages->objectAtIndex(i))->getValue()).c_str(),
                                                           FileUtils::getFilePath("Image/Main/UI/damage_number.png").c_str(), 50, 100, '0');
          damageLabel->setPosition(enemy->getPosition());
          float scale = enemy->getCurrentScale(enemy->getRow());
          damageLabel->setScale(scale);
          this->addChild(damageLabel);
          damageLabel->runAction(CCSequence::create(
                                                    CCFadeIn::create(0.2),
                                                    CCDelayTime::create(0.5),
                                                    CCFadeOut::create(0.2),
                                                    CCCallFunc::create(damageLabel, callfunc_selector(CCSprite::removeFromParentAndCleanup)),
                                                    NULL));
        }
        int getExp = ((CCInteger*)info->objectForKey("exp"))->getValue();
        _enemyManager->unshiftEnemiesQueue(_map->getFixedEnemies(preExp, preExp + getExp));
        this->checkLevelUp();
      } else if (performType == SkillPerformTypeNone) {
        // 何も実行しなかったとき
        _characterManager->useMP(-1);
      }
      _controller->updateSkills(_characterManager);
    } else if (trackNumber == 1) {
      stringstream ss;
      Enemy* nearest = _enemyManager->getNearestEnemy();
      if (nearest) {
        stringstream ss;
        ss << "counter" << nearest->getCounter() << ".wav";
        string file(_map->getPrefixedMusicName(ss.str().c_str()));
        Track* track = _music->pushTrack(file.c_str(), 1);
        
        int row = nearest->getRow();
        int denominator = (MAX_ROW + 1) * MAX_ROW / 2.0;
        int numerator = ((MAX_ROW - row) + 1) * (MAX_ROW - row) / 2.0;
        float volume = 1.0 * numerator / denominator;
        track->setVolume(volume);
      } else {
        string file(_map->getPrefixedMusicName("counter0.wav"));
        Track* track = _music->pushTrack(file.c_str(), 1);
        track->setVolume(0);
      }
    } else if (trackNumber == 2) {
      stringstream drumFileStream;
      drumFileStream << "drum" << _characterManager->getDrumLevel() << ".wav";
      string file(_map->getPrefixedMusicName(drumFileStream.str().c_str()));
      Track* t = _music->pushTrack(file.c_str(), 2);
      t->setVolume(0.7);
    }
  } else if (_state == VCStateStageSelect) {
    if (trackNumber == 0) {
      // ステージ移行処理
      Map* nextMap = _mapSelector->getSelectedMap();
      _map->release();
      nextMap->retain();
      _map = nextMap;
      _level = nextMap->createInitialLevel();
      this->removeChild(_mapSelector, true);
      _mapSelector->release();
      _mapSelector = NULL;
      TrackCache::sharedCache()->purgeAllTracks();
      this->pushInitialTracks(_map);
      this->updateGUI();
      _mapTurnCount = 0; // マップカウント0に戻す
      _state = VCStateMain;
    }
  }
}

void MainScene::trackDidFinishPlaying(Music *music, Track *finishedTrack, Track *nextTrack, int trackNumber) {
  if (trackNumber == 0) {
    // ターンカウントを進める
    ++_turnCount;
    ++_mapTurnCount;
    if (!_characterManager->isPerforming()) {
      _controller->resetAllTriggers();
      _enemyManager->purgeAllTrash();
    }
  }
}

void MainScene::updateGUI() {
  _hpLabel->setString(boost::lexical_cast<string>(_characterManager->getHP()).c_str());
  _mpLabel->setString(boost::lexical_cast<string>(_characterManager->getMP()).c_str());
  _levelLabel->setString(boost::lexical_cast<string>(_characterManager->getLevel()).c_str());
  _expLabel->setString(boost::lexical_cast<string>(_characterManager->getExp()).c_str());
  int currentLevel = _level->getLevel();
  int nextExp = _characterManager->getExpWithLevel(currentLevel + 1);
  _nextExpLabel->setString(boost::lexical_cast<string>(nextExp).c_str());
  _mapLabel->setString(_map->getName()->c_str());
}

void MainScene::pushInitialTracks(Map *map) {
  string main, counter, drum;
  if (map->getIntroCount() == 0) {
    // イントロなしのとき、いきなり曲を鳴らします
    main = map->getPrefixedMusicName("wait.wav");
    counter= map->getPrefixedMusicName("counter0.wav");
    drum = map->getPrefixedMusicName("drum0.wav");
  } else {
    // イントロありのとき、イントロを鳴らします
    main = map->getPrefixedMusicName("intro0.wav");
    counter = map->getPrefixedMusicName("silent.wav");
    drum = map->getPrefixedMusicName("silent.wav");
  }
  _music->pushTrack(main.c_str(), 0);
  _music->pushTrack(counter.c_str(), 1);
  _music->pushTrack(drum.c_str(), 2);
  _music->getTrack(1)->setVolume(0);
  _music->getTrack(2)->setVolume(0.7);
}

bool MainScene::checkLevelUp() {
  int currentLevel = _characterManager->getLevel();
  if (currentLevel != _preLevel) {
    _preLevel = currentLevel;
    _characterManager->updateParameters();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/levelup.mp3").c_str());
    _level = _map->createLevel(currentLevel);
    _enemyManager->setLevel(_level);
    this->updateGUI();
    if (_level->getLevel() >= _map->getMaxLevel()) {
      CCArray* maps = _map->getNextMaps();
      if (maps->count() >= 1) {
        _mapSelector = MapSelector::create();
        _mapSelector->retain();
        _mapSelector->setNextMaps(maps);
        if (maps->count() >= 2) {
          _mapSelector->setPosition(CCPointMake(0, 60));
          this->addChild(_mapSelector);
          _music->removeAllNextTracks();
          _music->pushTrack(FileUtils::getFilePath("Music/select/select_stage.wav").c_str(), 0);
          _music->pushTrack(FileUtils::getFilePath("Music/select/select_silent.wav").c_str(), 1);
          _music->pushTrack(FileUtils::getFilePath("Music/select/select_silent.wav").c_str(), 2);
        }
        _state = VCStateStageSelect;
      }
    }
    return true;
  }
  return false;
}
