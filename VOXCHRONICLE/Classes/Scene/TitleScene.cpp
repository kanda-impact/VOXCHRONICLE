//
//  TitleScene.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/10/27.
//
//

#include <sstream>
#include "SimpleAudioEngine.h"
#include "TitleScene.h"
#include "MainScene.h"
#include "FileUtils.h"
#include "DebugScene.h"
#include "macros.h"

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
  string images[] = {"logo.png", "title_start.png"};
  for (int i = 0; i < 2; ++i) {
    stringstream ss;
    ss << images[i];
    CCSprite* sprite = CCSprite::create(FileUtils::getFilePath(ss.str().c_str()).c_str());
    sprite->setPosition(ccp(winSize.width / 2, winSize.height / 2));
    this->addChild(sprite);
  }
  
  CCLabelTTF* startLabel = CCLabelTTF::create("Start", FONT_NAME, 32);
  CCLabelTTF* debugLabel = CCLabelTTF::create("Debug", FONT_NAME, 32);
  
  CCMenu* menu = CCMenu::create(CCMenuItemLabel::create(startLabel, this, menu_selector(TitleScene::onStartButtonPressed)),
                                CCMenuItemLabel::create(debugLabel, this, menu_selector(TitleScene::onDebugButtonPressed)),
                                NULL);
  menu->alignItemsHorizontallyWithPadding(50);
  menu->setPosition(ccp(winSize.width / 2, 80));
  this->addChild(menu);
  return true;
}

void TitleScene::registerWithTouchDispatcher() {
  CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool TitleScene::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent) {
  return true;
} 

void TitleScene::nextScene(CCLayer* layer) {
  CCScene* scene = CCScene::create();
  scene->addChild(layer);
  CCTransitionFade* transition = CCTransitionFade::create(0.5, scene);
  CCDirector::sharedDirector()->replaceScene(transition);
  CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
}

void TitleScene::onEnterTransitionDidFinish() {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(FileUtils::getFilePath("Music/general/title.mp3").c_str(), true);
}

void TitleScene::onStartButtonPressed(CCObject* sender) {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/start.mp3").c_str());
  MainScene* scene = MainScene::create();
  nextScene(scene);
}

void TitleScene::onDebugButtonPressed(CCObject* sender) {
  DebugScene* scene = DebugScene::create();
  nextScene(scene);
}