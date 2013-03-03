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
#include "DebugScene.h"
#include "macros.h"
#include "BufferCache.h"

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
  string images[] = {"logo.png", "title_start.png"};
  for (int i = 0; i < 2; ++i) {
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
  
  int r = rand() % 128;
  if (r == 0) {
    CCSprite* mask = CCSprite::create("easter0.png");
    CCAnimation* animation = CCAnimation::create();
    animation->addSpriteFrame(CCSpriteFrame::create(FileUtils::getFilePath("easter0.png").c_str(), CCRectMake(0, 0, 480, 320)));
    animation->addSpriteFrame(CCSpriteFrame::create(FileUtils::getFilePath("easter1.png").c_str(), CCRectMake(0, 0, 480, 320)));
    animation->setLoops(10);
    animation->setDelayPerUnit(10.0 / 60.0);
    mask->runAction(CCSequence::create(CCAnimate::create(animation),
                                       CCFadeOut::create(1.0f),
                                       CCPlace::create(ccp(1000, 1000)),
                                       NULL));
    this->addChild(mask);
    mask->setPosition(ccp(director->getWinSize().width / 2.0f, director->getWinSize().height / 2.0f));
  }
  
  CCMenuItemLabel* seOff = CCMenuItemLabel::create(CCLabelTTF::create("SE OFF", FONT_NAME, 24));
  seOff->setTag(0);
  CCMenuItemLabel* seOn = CCMenuItemLabel::create(CCLabelTTF::create("SE ON", FONT_NAME, 24));
  seOn->setTag(1);
  CCMenuItemToggle* item = CCMenuItemToggle::createWithTarget(this, menu_selector(TitleScene::onSETogglePressed), seOn, seOff, NULL);
  item->setSelectedIndex(SimpleAudioEngine::sharedEngine()->getEffectsVolume() == 0 ? 0 : 1);
  CCMenu* seMenu = CCMenu::create(item, NULL);
  seMenu->setPosition(ccp(280, 20));
  //this->addChild(seMenu);
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
  MainMenuScene* scene = new MainMenuScene(true);
  scene->autorelease();
  nextScene(scene);
}

void TitleScene::onDebugButtonPressed(CCObject* sender) {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/decide.mp3").c_str());
  DebugScene* scene = DebugScene::create();
  nextScene(scene);
}

void TitleScene::onSETogglePressed(cocos2d::CCObject *sender) {
  CCMenuItemToggle* item = (CCMenuItemToggle*)sender;
  SimpleAudioEngine::sharedEngine()->setEffectsVolume(item->getSelectedIndex());
}