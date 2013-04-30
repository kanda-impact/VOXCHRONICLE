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
  result->setPosition(ccp(director->getWinSize().width / 2.0, 280));
  CCSprite* congraturations = CCSprite::create("congratulations.png");
  congraturations->setPosition(ccp(director->getWinSize().width / 2.0, 230));
  this->addChild(result);
  this->addChild(congraturations);
  
  CCMenuItem* backItem = CCMenuItemImage::create("credit_back.png",
                                                 "credit_back_pressed.png",
                                                 this,
                                                 menu_selector(ResultScene::onBackButtonPressed));
  CCMenu* backMenu = CCMenu::create(backItem, NULL);
  backMenu->setPosition(ccp(440, 290));
  this->addChild(backMenu);
  _isAppeard = false;
  
  return true;
}

void ResultScene::buildUI() {
  CCDirector* director = CCDirector::sharedDirector();
  
  // history表示生成
  CCArray* history = _log->getMapHistory();
  CCNode* historyNode = CCNode::create();
  historyNode->setPosition(ccp(330, 55));
  CCObject* obj = NULL;
  const int xs[] = {0, 48, 96};
  const int ys[] = {0, 84, 0};
  int i = 0;
  CCARRAY_FOREACH(history, obj) {
    Map* map = new Map(((CCString*)obj)->getCString());
    map->autorelease();
    CCSprite* thumbnail = CCSprite::create(map->getThumbnailImageName().c_str());
    thumbnail->setPosition(ccp(xs[i], ys[i]));
    historyNode->addChild(thumbnail);
    ++i;
  }
  this->addChild(historyNode);
  
  CCLabelTTF* clearTurn = CCLabelTTF::create("クリアターン", "Helvetica", 24);
  clearTurn->setPosition(ccp(director->getWinSize().width / 2.0, 180));
  CCLabelTTF* clear = CCLabelTTF::create(lexical_cast<string>(_log->getCount(PlayLogKeyTurn)).c_str(), "Helvetica", 24);
  clear->setPosition(ccp(director->getWinSize().width / 2.0, 145));
  this->addChild(clearTurn);
  this->addChild(clear);
  
  CCLabelTTF* totalDamage = CCLabelTTF::create("受けたダメージ", "Helvetica", 18, CCSizeMake(150, 30), kCCTextAlignmentRight);
  totalDamage->setPosition(ccp(140, 90));
  CCLabelTTF* damage = CCLabelTTF::create(lexical_cast<string>(_log->getCount(PlayLogKeyHitDamage)).c_str(), "Helvetica", 18,
                                          CCSizeMake(60, 30), kCCTextAlignmentLeft);
  damage->setPosition(ccp(280, 90));
  this->addChild(totalDamage);
  this->addChild(damage);
  
  CCLabelTTF* continueLabel = CCLabelTTF::create("死んだ回数", "Helvetica", 18, CCSizeMake(150, 30), kCCTextAlignmentRight);
  continueLabel->setPosition(ccp(140, 45));
  CCLabelTTF* continueNumber = CCLabelTTF::create(lexical_cast<string>(_log->getCount(PlayLogKeyDead)).c_str(), "Helvetica", 18, CCSizeMake(60, 30), kCCTextAlignmentLeft);
  continueNumber->setPosition(ccp(280, 45));
  this->addChild(continueLabel);
  this->addChild(continueNumber);
  
  this->isTouchEnabled();
  
}

void ResultScene::onEnterTransitionDidFinish() {
  _isAppeard = true;
}


ResultScene::~ResultScene() {
  _log->release();
}

void ResultScene::registerWithTouchDispatcher() {
  CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 100, true);
}

bool ResultScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
  if (_isAppeard) {
    this->onBackButtonPressed(this);
  }
  return true;
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