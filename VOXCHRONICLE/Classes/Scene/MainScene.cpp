//
//  MainScene.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/8/28.
//
//

#include "MainScene.h"

using namespace cocos2d;
using namespace VISS;

bool MainScene::init() {
  if ( !CCLayer::init() ) {
    return false;
  }
  _music = new Music(2);
  _music->setTrack(new std::string("attack0.WAV"), 0);
  _music->setNextTrack(new std::string("attack1.WAV"), 0);
  _music->setTrack(new std::string("drum0.WAV"), 1);
  _music->setNextTrack(new std::string("drum1.WAV"), 1);
  _music->play();
  
  return true;
}

