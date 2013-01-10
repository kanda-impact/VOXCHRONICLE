//
//  PauseLayer.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/1/11.
//
//

#include "PauseLayer.h"
#include "macros.h"
#include "MainScene.h"
#include "TitleScene.h"
#include "FileUtils.h"

PauseLayer::PauseLayer() {
  _state = PauseLayerStateTop;
  
  this->setTouchEnabled(true);
  
  CCDirector* director = CCDirector::sharedDirector();
  
  CCLayerColor* background = CCLayerColor::create(ccc4(0, 0, 0, 128), director->getWinSize().width, director->getWinSize().height);
  this->addChild(background);
  
  CCLabelTTF* pause = CCLabelTTF::create("Pause", FONT_NAME, 48);
  pause->setPosition(ccp(director->getWinSize().width / 2.0, 280));
  this->addChild(pause);
  
  CCLabelTTF* replayLabel = CCLabelTTF::create("リプレイ", FONT_NAME, 24);
  CCLabelTTF* titleLabel = CCLabelTTF::create("タイトル", FONT_NAME, 24);
  CCLabelTTF* cancelLabel = CCLabelTTF::create("再開", FONT_NAME, 24);
  CCLabelTTF* yesLabel = CCLabelTTF::create("はい", FONT_NAME, 24);
  CCLabelTTF* noLabel = CCLabelTTF::create("いいえ", FONT_NAME, 24);
  
  _topMenu = CCMenu::create(CCMenuItemLabel::create(replayLabel, this, menu_selector(PauseLayer::onReplayPressed)),
                            CCMenuItemLabel::create(titleLabel, this, menu_selector(PauseLayer::onTitlePressed)),
                            CCMenuItemLabel::create(cancelLabel, this, menu_selector(PauseLayer::onCancelPressed)),
                            NULL);
  
  _confirmMenu = CCMenu::create(CCMenuItemLabel::create(yesLabel, this, menu_selector(PauseLayer::onYesPressed)),
                            CCMenuItemLabel::create(noLabel, this, menu_selector(PauseLayer::onNoPressed)),
                            NULL);
  _topMenu->setPosition(ccp(director->getWinSize().width / 2.0, 120));
  _topMenu->alignItemsVerticallyWithPadding(20);
  _confirmMenu->alignItemsVerticallyWithPadding(20);
  
  _descriptionLabel = CCLabelTTF::create("現在の進行は失われます。よろしいですか？", FONT_NAME, 16);
  _descriptionLabel->setPosition(ccp(director->getWinSize().width / 2.0, 230));
  _descriptionLabel->setVisible(false);
  this->addChild(_descriptionLabel);
  
  _topMenu->retain();
  _confirmMenu->retain();
  _descriptionLabel->retain();
  
  this->addChild(_topMenu);
  
}

PauseLayer::~PauseLayer() {
  _topMenu->release();
  _confirmMenu->release();
  _descriptionLabel->release();
}

void PauseLayer::registerWithTouchDispatcher() {
  CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -1, true);
}

bool PauseLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
  return true;
}

void PauseLayer::onReplayPressed(CCObject* sender) {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/decide.mp3").c_str());
  this->changeState(PauseLayerStateConfirmReplay);
}

void PauseLayer::onTitlePressed(CCObject* sender) {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/decide.mp3").c_str());
  this->changeState(PauseLayerStateConfirmTitle);
}

void PauseLayer::onCancelPressed(CCObject* sender) {
  MainScene* scene = (MainScene*)this->getParent();
  scene->setPause(false);
  this->removeFromParentAndCleanup(true);
}

void PauseLayer::onYesPressed(CCObject* sender) {
  MainScene* scene = (MainScene*)this->getParent();
  scene->setPause(false);
  this->removeFromParentAndCleanup(true);
  if (_state == PauseLayerStateConfirmReplay) {
    scene->replayButtonPressed(this);
  } else if (_state == PauseLayerStateConfirmTitle) {
    scene->titleButtonPressed(this);
  }
}

void PauseLayer::onNoPressed(CCObject* sender) {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/cancel.mp3").c_str());
  this->changeState(PauseLayerStateTop);
}

void PauseLayer::changeState(PauseLayerState newState) {
  if (_state == PauseLayerStateTop) {
    this->removeChild(_topMenu, true);
  } else {
    this->removeChild(_confirmMenu, true);
    _descriptionLabel->setVisible(false);
  }
  if (newState == PauseLayerStateTop) {
    this->addChild(_topMenu);
  } else {
    this->addChild(_confirmMenu);
    _descriptionLabel->setVisible(true);
  }
  _state = newState;
}