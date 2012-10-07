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

using namespace std;
using namespace cocos2d;
using namespace VISS;

bool MainScene::init() {
  if ( !CCLayer::init() ) {
    return false;
  }
  _music = new Music(4);
  _music->setTrackDidBackFunction(boost::bind(&MainScene::trackDidBack, this, _1, _2, _3));
  _music->setTrackDidFinishFunction(boost::bind(&MainScene::trackDidFinishPlaying, this, _1, _2, _3, _4));
  _music->setTrackWillFinishFunction(boost::bind(&MainScene::trackWillFinishPlaying, this, _1, _2, _3, _4));
  
  _music->pushTrack("dub_silent.wav", 0);
  _music->pushTrack("dub_ura00.wav", 1);
  _music->pushTrack("dub_basschord00.wav", 2);
  _music->pushTrack("dub_drum00.wav", 3);
  _music->getTrack(1)->setVolume(0);
  
  _enemyManager = EnemyManager::create();
  _enemyManager->retain();
  this->addChild(_enemyManager);
  
  CCDirector* director = CCDirector::sharedDirector();
  _controller = Controller::create();
  _controller->retain();
  _characterManager = new CharacterManager();
  _characterManager->retain();
  _controller->setSkills(_characterManager->getCurrentCharacter()->getSkills());
  CCSize size = director->getWinSize();
  this->addChild(_controller);
  
  _map = new Map("test");
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
  this->addChild(_levelLabel);
  this->addChild(_hpLabel);
  this->addChild(_mpLabel);
  this->addChild(_expLabel);
  this->addChild(_nextExpLabel);
  this->updateGUI();
  
  this->scheduleUpdate();
  
  _turnCount = 0;
  return true;
}

MainScene::~MainScene() {
  delete _music;
  _controller->release();
  _enemyManager->release();
  _characterManager->release();
}

void MainScene::update(float dt) {
  _controller->setEnable(!_characterManager->isPerforming());
}

void MainScene::onEnterTransitionDidFinish() {
  _music->play();
}

void MainScene::trackDidBack(Music *music, Track *currentTrack, int trackNumber) {
  if (trackNumber == 0) {
    _enemyManager->lotPopEnemy();
    CCObject* obj = NULL;
    CCARRAY_FOREACH(_enemyManager->getEnemies(), obj) {
      Enemy* enemy = (Enemy*)obj;
      if (enemy->getRow() > 0) {
        if (enemy->canMove()) {
          enemy->moveRow(-1);
        }
      } else {
        DamageType result = _characterManager->damage(enemy, 1);
        if (result == DamageTypeDeath) {
          std::cout << "game over" << std::endl;
        }
        _enemyManager->removeEnemy(enemy);
      }
    }
    this->updateGUI();
  }
}

void MainScene::trackWillFinishPlaying(Music *music, Track *currentTrack, Track *nextTrack, int trackNumber) {
  if (trackNumber == 0) {
    Skill* skill = NULL;
    if (_characterManager->isPerforming()) {
      skill = _characterManager->getCurrentSkill();
    } else {
      skill = _controller->currentTriggerSkill();
    }
    std::stringstream ss;
    const char* name = _characterManager->performSkill(skill);
    ss << name << ".wav";
    string file(_map->getPrefixedMusicName(ss.str().c_str()));
    _music->pushTrack(file.c_str(), 0);
    if (skill) {
      int currentLevel = _characterManager->getLevel();
      _enemyManager->performSkill(skill, _characterManager);
      int newLevel = _characterManager->getLevel();
      if (currentLevel != newLevel) {
        cout << "Level Up!" << endl;
        _level = _map->createLevel(newLevel);
        _enemyManager->setLevel(_level);
        this->updateGUI();
        if (_level->getLevel() == _map->getMaxLevel()) {
          MapSelector* selector = MapSelector::create();
          selector->setPosition(CCPointMake(0, 60));
          this->addChild(selector);
        }
      }
    }
    _controller->setSkills(_characterManager->getCurrentCharacter()->getSkills());
    ++_turnCount;
  } else if (trackNumber == 1) {
    stringstream ss;
    Enemy* nearest = _enemyManager->getNearestEnemy();
    if (nearest) {
      stringstream ss;
      ss << "ura0" << nearest->getCounter() << ".wav";
      string file(_map->getPrefixedMusicName(ss.str().c_str()));
      Track* track = _music->pushTrack(file.c_str(), 1);
      
      int row = nearest->getRow();
      int denominator = (MAX_ROW + 1) * MAX_ROW / 2.0;
      int numerator = ((MAX_ROW - row) + 1) * (MAX_ROW - row) / 2.0;
      float volume = 1.0 * numerator / denominator;
      track->setVolume(volume);
    } else {
      string file(_map->getPrefixedMusicName("ura00.wav"));
      Track* track = _music->pushTrack(file.c_str(), 1);
      track->setVolume(0);
    }
    
  } else if (trackNumber == 2) {
    stringstream ss;
    ss << "basschord0" << _turnCount % 4 << ".wav";
    string file(_map->getPrefixedMusicName(ss.str().c_str()));
    _music->pushTrack(file.c_str(), 2);
  } else if (trackNumber == 3) {
    string file(_map->getPrefixedMusicName("drum00.wav"));
    _music->pushTrack(file.c_str(), 3);
  }
}

void MainScene::trackDidFinishPlaying(Music *music, Track *finishedTrack, Track *nextTrack, int trackNumber) {
  if (trackNumber == 0) {
    if (!_characterManager->isPerforming()) {
      _controller->resetAllTriggers();
      _enemyManager->purgeAllTrash();
    }
  }
}

void MainScene::updateGUI() {
  stringstream ss;
  ss <<_characterManager->getHP();
  _hpLabel->setString(ss.str().c_str());
  ss.str("");
  ss <<_characterManager->getMP();
  _mpLabel->setString(ss.str().c_str());
  ss.str("");
  ss << _characterManager->getLevel();
  _levelLabel->setString(ss.str().c_str());
  ss.str("");
  ss << _characterManager->getExp();
  _expLabel->setString(ss.str().c_str());
  ss.str("");
  int currentLevel = _level->getLevel();
  int nextExp = _characterManager->getExpWithLevel(currentLevel + 1);
  ss << nextExp;
  _nextExpLabel->setString(ss.str().c_str());
}
