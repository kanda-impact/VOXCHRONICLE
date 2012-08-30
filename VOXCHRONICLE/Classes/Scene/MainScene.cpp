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
  const std::string* filename = new std::string("attack0.WAV");
  _test = new Track(filename);
  _test->play();
  return true;
}

