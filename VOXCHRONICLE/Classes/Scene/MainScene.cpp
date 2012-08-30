//
//  MainScene.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/8/28.
//
//

#include "MainScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

bool MainScene::init() {
  if ( !CCLayer::init() ) {
    return false;
  }
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("attack0.WAV");
  return true;
}

