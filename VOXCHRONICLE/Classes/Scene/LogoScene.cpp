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
  if ( !CCLayer::init() ) {
    return false;
  }
  this->setTouchEnabled(true);
  CCDirector* director = CCDirector::sharedDirector();
  CCSize winSize = director->getWinSize();
  CCSprite* logo = CCSprite::create("kawaz.png");
  CCLayerColor* background = CCLayerColor::create(ccc4(255, 255, 255, 255), winSize.width, winSize.height);
  std::cout << winSize.width << "," << winSize.height;
  logo->setPosition(ccp(winSize.width / 2, winSize.height / 2));
  logo->setOpacity(0);
  logo->runAction(CCSequence::create(
                                     CCFadeIn::create(2.0),
                                     CCDelayTime::create(2.0),
                                     CCFadeOut::create(2.0),
                                     CCCallFunc::actionWithTarget(this, callfunc_selector(LogoScene::nextScene)),
                                     NULL));
  this->addChild(background);
  this->addChild(logo);

  return true;
}

void LogoScene::menuCloseCallback(CCObject* pSender) {
  CCDirector::sharedDirector()->end();
  
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
  exit(0);
#endif
  
}

void LogoScene::registerWithTouchDispatcher() {
  CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool LogoScene::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent) {
  CCLog("test");
  nextScene();
  return true;
}

void LogoScene::nextScene() {
  CCTransitionFade* transition = CCTransitionFade::transitionWithDuration(1.0, LogoScene::scene());
  CCDirector::sharedDirector()->replaceScene(transition);
}