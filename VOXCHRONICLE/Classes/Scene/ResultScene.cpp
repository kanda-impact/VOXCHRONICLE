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

#include "KWAlert.h"

using namespace boost;

bool ResultScene::init () {
  if (!CCLayer::init()) {
    return false;
  }
  
  CCDirector* director = CCDirector::sharedDirector();
  
  CCSprite* result = CCSprite::create("result.png");
  result->setPosition(ccp(director->getWinSize().width / 2.0, 280));
  CCSprite* congraturations = CCSprite::create("congratulations.png");
  congraturations->setPosition(ccp(director->getWinSize().width / 2.0, 240));
  this->addChild(result);
  this->addChild(congraturations);
  
  CCMenuItem* backItem = CCMenuItemImage::create("credit_back.png",
                                                 "credit_back_pressed.png",
                                                 this,
                                                 menu_selector(ResultScene::onBackButtonPressed));
  _backMenu = CCMenu::create(backItem, NULL);
  _backMenu->retain();
  _backMenu->setPosition(ccp(430, 290));
  this->addChild(_backMenu);
  _isAppeard = false;
  
  return true;
}

void ResultScene::buildUI() {
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
  
  // ハイスコア
  CCString* lastMap = (CCString*)history->lastObject();
  int currentScore = _log->getCount(PlayLogKeyTurn);
  bool isHighScore = SaveData::sharedData()->updateScore(lastMap->getCString(), currentScore);
  
  CCLabelTTF* routeLabel = CCLabelTTF::create("クリアルート", "Helvetica", 18, CCSizeMake(150, 30), kCCTextAlignmentRight, kCCVerticalTextAlignmentCenter);
  CCLabelTTF* route = CCLabelTTF::create("A", "Helvetica", 18, CCSizeMake(50, 30), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
  routeLabel->setPosition(ccp(190, 170));
  route->setPosition(ccp(305, 170));
  this->addChild(routeLabel);
  this->addChild(route);
  
  // クリアルート表示。ハードコード
  if (string(lastMap->getCString()) == "3a_ruin") {
    route->setString("A");
  } else if (string(lastMap->getCString()) == "3b_castle") {
    route->setString("B");
  } else if (string(lastMap->getCString()) == "3c_ocean") {
    route->setString("C");
  } else if (string(lastMap->getCString()) == "3d_space") {
    route->setString("D");
  }
  
  int highScore = SaveData::sharedData()->getScore(lastMap->getCString());
  
  if (currentScore < highScore) {
    highScore = currentScore;
  }
  
  CCLabelTTF* clearTurn = CCLabelTTF::create("クリアターン", "Helvetica", 24, CCSizeMake(150, 30), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
  clearTurn->setPosition(ccp(80, 180));
  CCLabelTTF* clear = CCLabelTTF::create(lexical_cast<string>(_log->getCount(PlayLogKeyTurn)).c_str(), "Helvetica", 24, CCSizeMake(150, 30), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
  clear->setPosition(ccp(80, 145));
  this->addChild(clearTurn);
  this->addChild(clear);
  
  CCLabelTTF* highScoreLabel = CCLabelTTF::create("過去最速", "Helvetica", 18, CCSizeMake(150, 30), kCCTextAlignmentRight, kCCVerticalTextAlignmentCenter);
  highScoreLabel->setPosition(ccp(190, 140));
  CCLabelTTF* highScoreTurnLabel = CCLabelTTF::create(lexical_cast<string>(highScore).c_str(), "Helvetica", 18, CCSizeMake(50, 30), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
  highScoreTurnLabel->setPosition(ccp(305, 140));
  this->addChild(highScoreTurnLabel);
  this->addChild(highScoreLabel);
  
  if (isHighScore) {
    CCAction* blink0 = CCRepeatForever::create(CCSequence::createWithTwoActions(CCFadeTo::create(0.08, 128),
                                                                               CCFadeTo::create(0.08, 255)));
    CCAction* blink1 = CCRepeatForever::create(CCSequence::createWithTwoActions(CCFadeTo::create(0.08, 128),
                                                                               CCFadeTo::create(0.08, 255)));
    CCAction* blink2 = CCRepeatForever::create(CCSequence::createWithTwoActions(CCFadeTo::create(0.08, 128),
                                                                               CCFadeTo::create(0.08, 255)));
    CCAction* blink3 = CCRepeatForever::create(CCSequence::createWithTwoActions(CCFadeTo::create(0.08, 128),
                                                                               CCFadeTo::create(0.08, 255)));
    clearTurn->runAction(blink0);
    clear->runAction(blink1);
    highScoreLabel->runAction(blink2);
    highScoreTurnLabel->runAction(blink3);
  }
  
  SaveData::sharedData()->save();
  
  CCLabelTTF* totalDamage = CCLabelTTF::create("受けたダメージ", "Helvetica", 16, CCSizeMake(150, 30), kCCTextAlignmentRight);
  totalDamage->setPosition(ccp(140, 90));
  CCLabelTTF* damage = CCLabelTTF::create(lexical_cast<string>(_log->getCount(PlayLogKeyHitDamage)).c_str(), "Helvetica", 16,
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
  
  this->setTouchEnabled(true);
}

void ResultScene::onEnterTransitionDidFinish() {
  _isAppeard = true;
  // 初回クリア時
  if (SaveData::sharedData()->getCountFor(SaveDataCountKeyClear) <= 1) { // ポップアップを出します
    this->setTouchEnabled(false);
    LuaObject* setting = LuaObject::create("setting");
    CCDirector* director = CCDirector::sharedDirector();
    CCArray* names = CCArray::create(CCString::create("OK"), NULL);
    KWAlert* alert = new KWAlert("dialog_window.png", names);
    alert->setPosition(ccp(director->getWinSize().width / 2.0, director->getWinSize().height / 2.0));
    alert->autorelease();
    this->addChild(alert);
    alert->setText(setting->getString("extraUnlockMessage"));
    alert->setDelegate(this);
    alert->show();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/unlock_achievement.mp3").c_str());
    _backMenu->setEnabled(false);
  }
}


ResultScene::~ResultScene() {
  _log->release();
  _backMenu->release();
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

void ResultScene::clickedButtonAtIndex(KWAlert *alert, int index) {
  alert->dismiss();
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/window_close.mp3").c_str());
  this->setTouchEnabled(true);
  _backMenu->setEnabled(true);
}