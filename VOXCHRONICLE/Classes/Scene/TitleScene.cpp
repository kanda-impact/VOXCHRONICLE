//
//  TitleScene.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/10/27.
//
//

#include "SimpleAudioEngine.h"
#include "TitleScene.h"
#include "MainScene.h"
#include "FileUtils.h"

using namespace cocos2d;

CCScene* TitleScene::scene() {
  CCScene* scene = CCScene::create();
  
  TitleScene* layer = TitleScene::create();
  
  scene->addChild(layer);
  
  return scene;
}

bool TitleScene::init() {
  if ( !CCLayer::init() ) {
    return false;
  }
  this->setTouchEnabled(true);
  CCDirector* director = CCDirector::sharedDirector();
  CCSize winSize = director->getWinSize();
  CCSprite* title = CCSprite::create(FileUtils::getFilePath("Image/Title/title.png").c_str());
  title->setPosition(ccp(winSize.width / 2, winSize.height / 2));
  this->addChild(title);
  
  return true;
}

void TitleScene::registerWithTouchDispatcher() {
  CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool TitleScene::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent) {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/decide.mp3").c_str());
  nextScene();
  return true;
}

void TitleScene::nextScene() {
  CCScene* scene = CCScene::create();
  scene->addChild(MainScene::create());
  CCTransitionFade* transition = CCTransitionFade::create(0.5, scene);
  CCDirector::sharedDirector()->replaceScene(transition);
}