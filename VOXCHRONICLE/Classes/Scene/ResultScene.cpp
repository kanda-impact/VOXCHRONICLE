//
//  ResultScene.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/4/13.
//
//

#include "ResultScene.h"
#include "FileUtils.h"
#include "TitleScene.h"
#include <boost/lexical_cast.hpp>

using namespace boost;

bool ResultScene::init () {
  if (!CCLayer::init()) {
    return false;
  }
  
  CCDirector* director = CCDirector::sharedDirector();
  
  CCSprite* result = CCSprite::create("result.png");
  result->setPosition(ccp(director->getWinSize().width / 2.0, 300));
  CCSprite* congraturations = CCSprite::create("congratulations.png");
  congraturations->setPosition(ccp(director->getWinSize().width / 2.0, 240));
  this->addChild(result);
  this->addChild(congraturations);
  
  CCMenuItem* backItem = CCMenuItemImage::create("credit_back.png",
                                                 "credit_back_pressed.png",
                                                 this,
                                                 menu_selector(ResultScene::onBackButtonPressed));
  CCMenu* backMenu = CCMenu::create(backItem, NULL);
  backMenu->setPosition(ccp(440, 290));
  this->addChild(backMenu);
  
  return true;
}

void ResultScene::buildUI() {
  CCDirector* director = CCDirector::sharedDirector();
  
  CCLabelTTF* clearTurn = CCLabelTTF::create("クリアターン", "Helvetica", 32);
  clearTurn->setPosition(ccp(director->getWinSize().width / 2.0, 180));
  CCLabelTTF* clear = CCLabelTTF::create(lexical_cast<string>(_log->getCount(PlayLogKeyTurn)).c_str(), "Helvetica", 32);
  clear->setPosition(ccp(director->getWinSize().width / 2.0, 145));
  this->addChild(clearTurn);
  this->addChild(clear);
  
  CCLabelTTF* totalDamage = CCLabelTTF::create("受けたダメージ", "Helvetica", 18, CCSizeMake(150, 30), kCCTextAlignmentRight);
  totalDamage->setPosition(ccp(140, 90));
  CCLabelTTF* damage = CCLabelTTF::create(lexical_cast<string>(_log->getCount(PlayLogKeyHitDamage)).c_str(), "Helvetica", 18,
                                          CCSizeMake(60, 30), kCCTextAlignmentRight);
  damage->setPosition(ccp(280, 90));
  this->addChild(totalDamage);
  this->addChild(damage);
  
  CCLabelTTF* continueLabel = CCLabelTTF::create("死んだ回数", "Helvetica", 18, CCSizeMake(150, 30), kCCTextAlignmentRight);
  continueLabel->setPosition(ccp(140, 45));
  CCLabelTTF* continueNumber = CCLabelTTF::create(lexical_cast<string>(_log->getCount(PlayLogKeyDead)).c_str(), "Helvetica", 18, CCSizeMake(60, 30), kCCTextAlignmentRight);
  continueNumber->setPosition(ccp(280, 45));
  this->addChild(continueLabel);
  this->addChild(continueNumber);
}


ResultScene::~ResultScene() {
  _log->release();
}

void ResultScene::setPlayLog(PlayLog *log) {
  if (_log) {
    _log->release();
  }
  _log = log;
  if (log) {
    log->retain();
  }
}

void ResultScene::onBackButtonPressed(cocos2d::CCObject *sender) {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/cancel.mp3").c_str());
  CCScene* scene = CCScene::create();
  scene->addChild(TitleScene::create());
  CCTransitionFade* fade = CCTransitionFade::create(2.0f, scene);
  CCDirector::sharedDirector()->replaceScene(fade);
}