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
  
  _music->pushTrack("dub_silent.wav", 0);
  _music->pushTrack("dub_basschord00.wav", 1);
  _music->pushTrack("dub_drum00.wav", 2);
  
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
  
  _hpLabel = CCLabelTTF::create("", "Helvetica", 16);
  _hpLabel->setPosition(CCPointMake(400, 290));
  _mpLabel = CCLabelTTF::create("", "Helvetica", 16);
  _mpLabel->setPosition(CCPointMake(400, 270));
  this->addChild(_hpLabel);
  this->addChild(_mpLabel);
  this->updateGUI();
  
  _map = new Map("test");
  
  return true;
}

MainScene::~MainScene() {
  delete _music;
  _controller->release();
  _enemyManager->release();
  _characterManager->release();
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
        enemy->moveRow(-1);
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
    Skill* skill = _controller->currentTriggerSkill();
    std::stringstream ss;
    const char* name = _characterManager->performSkill(skill);
    ss << name << ".wav";
    string file(_map->getPrefixedMusicName(ss.str().c_str()));
    _music->pushTrack(file.c_str(), 0);
    if (skill) _enemyManager->performSkill(skill, _characterManager);
    _controller->setSkills(_characterManager->getCurrentCharacter()->getSkills());
  } else if (trackNumber == 1) {
    string file(_map->getPrefixedMusicName("basschord00.wav"));
    _music->pushTrack(file.c_str(), 1);
  } else if (trackNumber == 2) {
    string file(_map->getPrefixedMusicName("drum00.wav"));
    _music->pushTrack(file.c_str(), 2);
  }
}

void MainScene::trackDidFinishPlaying(Music *music, Track *finishedTrack, Track *nextTrack, int trackNumber) {
  if (trackNumber == 0) {
    _controller->resetAllTriggers();
    std::cout << "next Track" << std::endl;
  }
}

void MainScene::updateGUI() {
  stringstream ss;
  ss <<_characterManager->getHP();
  _hpLabel->setString(ss.str().c_str());
  ss.str("");
  ss <<_characterManager->getMP();
  _mpLabel->setString(ss.str().c_str());
  
}
