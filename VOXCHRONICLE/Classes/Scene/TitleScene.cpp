//
//  TitleScene.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/10/27.
//
//

typedef enum {
  TitleSceneTagDemoText,
  TitleSceneTagDemoBackground
} TitleSceneTag;

#include <sstream>
#include "SimpleAudioEngine.h"
#include "TitleScene.h"
#include "MainMenuScene.h"
#include "FileUtils.h"
#include "FreePlayScene.h"
#include "macros.h"
#include "BufferCache.h"
#include "InitialScene.h"

#include "KWAlert.h"

#include <boost/lexical_cast.hpp>

#include "CCRemoveFromParentAction.h"

#include "UIApplicationWrapper.h"

using namespace cocos2d;
using namespace boost;

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
  string images[] = {"logo.png"};
  for (int i = 0; i < 1; ++i) {
    stringstream ss;
    ss << "Image/" << images[i];
    CCSprite* sprite = CCSprite::create(FileUtils::getFilePath(ss.str().c_str()).c_str());
    sprite->setPosition(ccp(winSize.width / 2, winSize.height / 2));
    this->addChild(sprite);
  }
  
#ifndef RELEASE
  //CCLabelTTF* startLabel = CCLabelTTF::create("Start", FONT_NAME, 32);
  CCLabelTTF* debugLabel = CCLabelTTF::create("Debug", FONT_NAME, 32);
  //CCMenuItemLabel::create(startLabel, this, menu_selector(TitleScene::onStartButtonPressed))
  CCMenu* menu = CCMenu::create(CCMenuItemLabel::create(debugLabel, this, menu_selector(TitleScene::onDebugButtonPressed)),
                                NULL);
  menu->alignItemsHorizontallyWithPadding(50);
  menu->setPosition(ccp(winSize.width / 2, 80));
  this->addChild(menu);
#endif

  CCMenuItemLabel* seOff = CCMenuItemLabel::create(CCLabelTTF::create("SE OFF", FONT_NAME, 24));
  seOff->setTag(0);
  CCMenuItemLabel* seOn = CCMenuItemLabel::create(CCLabelTTF::create("SE ON", FONT_NAME, 24));
  seOn->setTag(1);
  CCMenuItemToggle* item = CCMenuItemToggle::createWithTarget(this, menu_selector(TitleScene::onSETogglePressed), seOn, seOff, NULL);
  item->setSelectedIndex(SimpleAudioEngine::sharedEngine()->getEffectsVolume() == 0 ? 0 : 1);
  CCMenu* seMenu = CCMenu::create(item, NULL);
  seMenu->setPosition(ccp(280, 20));
  //this->addChild(seMenu);
  
  CCLabelTTF* credit = CCLabelTTF::create("2009-2013 Kawaz all rights reserved.", "Helvetica", 12);
  credit->setColor(ccc3(220, 220, 220));
  credit->setPosition(ccp(director->getWinSize().width / 2.0, 25));
  this->addChild(credit);
  
  this->setTouchEnabled(true);
  
  _isDemo = false;
  _demo = new LuaObject("demo.lua");
  
  _touchToStart = CCLabelTTF::create("touch to start", "Helvetica", 32);
  _touchToStart->setPosition(ccp(director->getWinSize().width / 2.0, 70));
  _touchToStart->runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(CCFadeTo::create(1.5f, 64), CCFadeTo::create(1.5f, 255))));
  this->addChild(_touchToStart);
  _touchToStart->retain();
  
  _shakeCount = 0;
  _isShaking = false;
  
  this->setAccelerometerEnabled(true);

  return true;
}

TitleScene::~TitleScene() {
  _demo->release();
  _touchToStart->release();
}

void TitleScene::nextScene(CCLayer* layer) {
  CCScene* scene = CCScene::create();
  scene->addChild(layer);
  CCTransitionFade* transition = CCTransitionFade::create(0.5, scene);
  CCDirector::sharedDirector()->replaceScene(transition);
}

void TitleScene::onEnterTransitionDidFinish() {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(FileUtils::getFilePath("Music/general/title.mp3").c_str(), true);
  this->scheduleOnce(schedule_selector(TitleScene::onDemoStart), _demo->getNumber("delay"));
}

void TitleScene::onStartButtonPressed(CCObject* sender) {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/start.mp3").c_str());
  CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
  if (SaveData::sharedData()->isInitialBoot()) {
    InitialScene* scene = InitialScene::create();
    nextScene(scene);
    SaveData::sharedData()->setInitialBoot(false);
  } else {
    MainMenuScene* scene = new MainMenuScene(true);
    scene->autorelease();
    nextScene(scene);
  }
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

void TitleScene::registerWithTouchDispatcher() {
  CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 100, true);
}

bool TitleScene::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent) {
  if (_isDemo) {
    _isDemo = false;
    this->removeDemo();
  } else {
    this->onStartButtonPressed(this);
  }
  return false;
}

void TitleScene::onDemoStart() {
  SaveData* data = SaveData::sharedData();
  _isDemo = true;
  UIApplicationWrapper::sharedApplication()->setIdleTimerDisabled(true);
  CCDirector* director = CCDirector::sharedDirector();
  string text = _demo->getString("text");
  CCLabelTTF* label = CCLabelTTF::create(text.c_str(),
                                         "Helvetica",
                                         21,
                                         CCSizeMake(director->getWinSize().width - 50, _demo->getNumber("boxHeight")),
                                         kCCTextAlignmentCenter,
                                         kCCVerticalTextAlignmentCenter);
  CCLabelTTF* shadowLabel = CCLabelTTF::create(text.c_str(),
                                               "Helvetica",
                                               21,
                                               CCSizeMake(director->getWinSize().width - 50, _demo->getNumber("boxHeight")),
                                               kCCTextAlignmentCenter,
                                               kCCVerticalTextAlignmentCenter);
  
  label->setColor(ccc3(255, 255, 255));
  shadowLabel->setColor(ccc3(33, 33, 33));
  shadowLabel->setPosition(ccpAdd(label->getPosition(), ccp(2, -2)));
  
  CCLayerColor* bg = CCLayerColor::create(ccc4(0, 0, 0, 128), director->getWinSize().width, director->getWinSize().height);
  this->addChild(bg, 0, TitleSceneTagDemoBackground);
  CCLayer* labels = CCLayer::create();
  
  labels->addChild(shadowLabel);
  labels->setPosition(ccp(director->getWinSize().width / 2.0f, - director->getWinSize().height / 2.0f - 50));
  labels->addChild(label);
  bg->addChild(labels, 0, TitleSceneTagDemoText);
  
  bg->setOpacity(0);
  bg->runAction(CCFadeTo::create(0.5, 128));
  labels->runAction(CCSequence::create(CCDelayTime::create(0.5f),
                                       CCMoveTo::create(_demo->getNumber("scrollDuration"),
                                                        ccp(_demo->getNumber("moveToX"), _demo->getNumber("moveToY"))),
                                       CCDelayTime::create(_demo->getNumber("stopDuration")),
                                       CCCallFunc::create(this, callfunc_selector(TitleScene::onDemoEnd)),
                                       NULL)
  );
  if (data->isFullVoice()) {
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.4f);
    SimpleAudioEngine::sharedEngine()->playEffect("demo.mp3");
  }
  _touchToStart->setVisible(false);
}

void TitleScene::onDemoEnd() {
  _isDemo = false;
  this->removeDemo();
}

void TitleScene::removeDemo() {
  UIApplicationWrapper::sharedApplication()->setIdleTimerDisabled(false);
  SimpleAudioEngine::sharedEngine()->stopAllEffects();
  _touchToStart->setVisible(true);
  CCNode* demo = this->getChildByTag(TitleSceneTagDemoBackground);
  CCNode* label = demo->getChildByTag(TitleSceneTagDemoText);
  demo->removeChild(label, true);
  demo->runAction(CCSequence::create(CCFadeTo::create(0.5f, 0), CCRemoveFromParentAction::create(), NULL));
  SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1.0f);
}

void TitleScene::didAccelerate(CCAcceleration *pAccelerationValue) {
  SaveData* data = SaveData::sharedData();
  if (!data->isFullVoice()) {
    if (pAccelerationValue->x > 1.8 || pAccelerationValue->y > 1.8 || pAccelerationValue->z > 1.8) {
      if (!_isShaking) { // 3回振るとチュートリアル解放
        _isShaking = true;
        ++_shakeCount;
        if (_shakeCount >= 3) {
          int number = rand() % 3;
          SimpleAudioEngine::sharedEngine()->playEffect(("fullvoice" + lexical_cast<string>(number) + ".mp3").c_str());
          data->setFullVoice(true);
          data->unlockAchievement("unlockFullVoice");
        }
      }
    } else {
      _isShaking = false;
    }
  }
}