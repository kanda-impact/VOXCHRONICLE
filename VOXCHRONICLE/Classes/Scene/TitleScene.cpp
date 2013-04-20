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
#include "MainMenuScene.h"
#include "FileUtils.h"
#include "FreePlayScene.h"
#include "macros.h"
#include "BufferCache.h"
#include "StaffRollScene.h"

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
  VISS::BufferCache::sharedCache()->purgeAllBuffers();
  this->setTouchEnabled(true);
  CCDirector* director = CCDirector::sharedDirector();
  CCSize winSize = director->getWinSize();
  string images[] = {"logo.png"};
  for (int i = 0; i < 1; ++i) {
    stringstream ss;
    ss << "Image/" << images[i];
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
  
  CCMenuItemLabel* seOff = CCMenuItemLabel::create(CCLabelTTF::create("SE OFF", FONT_NAME, 24));
  seOff->setTag(0);
  CCMenuItemLabel* seOn = CCMenuItemLabel::create(CCLabelTTF::create("SE ON", FONT_NAME, 24));
  seOn->setTag(1);
  CCMenuItemToggle* item = CCMenuItemToggle::createWithTarget(this, menu_selector(TitleScene::onSETogglePressed), seOn, seOff, NULL);
  item->setSelectedIndex(SimpleAudioEngine::sharedEngine()->getEffectsVolume() == 0 ? 0 : 1);
  CCMenu* seMenu = CCMenu::create(item, NULL);
  seMenu->setPosition(ccp(280, 20));
  this->addChild(seMenu);
  
  CCLabelTTF* credit = CCLabelTTF::create("2009-2013 Kawaz all rights reserved.", "Helvetica", 12);
  credit->setColor(ccc3(220, 220, 220));
  credit->setPosition(ccp(director->getWinSize().width / 2.0, 25));
  this->addChild(credit);
  
  return true;
}

void TitleScene::nextScene(CCLayer* layer) {
  CCScene* scene = CCScene::create();
  scene->addChild(layer);
  CCTransitionFade* transition = CCTransitionFade::create(0.5, scene);
  CCDirector::sharedDirector()->replaceScene(transition);
}

void TitleScene::onEnterTransitionDidFinish() {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(FileUtils::getFilePath("Music/general/title.mp3").c_str(), true);
}

void TitleScene::onStartButtonPressed(CCObject* sender) {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/start.mp3").c_str());
  MainMenuScene* scene = new MainMenuScene(true);
  scene->autorelease();
  CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
  nextScene(scene);
}

void TitleScene::onDebugButtonPressed(CCObject* sender) {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/decide.mp3").c_str());
  FreePlayScene* scene = FreePlayScene::create("debug.lua", true);
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(FileUtils::getFilePath("Music/general/menu.mp3").c_str(), true);
  nextScene(scene);
}

void TitleScene::onSETogglePressed(cocos2d::CCObject *sender) {
  CCMenuItemToggle* item = (CCMenuItemToggle*)sender;
  SimpleAudioEngine::sharedEngine()->setEffectsVolume(item->getSelectedIndex());
}
