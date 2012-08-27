//
//  LogoScene.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/8/27.
//
//

#include "LogoScene.h"
using namespace cocos2d;

CCScene* LogoScene::scene() {
  CCScene* scene = CCScene::create();
  
  LogoScene* layer = LogoScene::create();
  
  scene->addChild(layer);
  return scene;
}

bool LogoScene::init() {
  //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() ) {
        return false;
    }
  
  return true;
}

void LogoScene::menuCloseCallback(CCObject* pSender) {
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}