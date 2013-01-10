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

PauseLayer::PauseLayer() {
  _state = PauseLayerStateTop;
  
  this->setTouchEnabled(true);
  
  CCDirector* director = CCDirector::sharedDirector();
  
  CCLayerColor* background = CCLayerColor::create(ccc4(255, 255, 255, 200), director->getWinSize().width, director->getWinSize().height);
  this->addChild(background);
  
  CCLabelTTF* pause = CCLabelTTF::create("Pause", FONT_NAME, 48);
  pause->setPosition(ccp(director->getWinSize().width / 2.0, 280));
  
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
  _topMenu->alignItemsVerticallyWithPadding(40);
  _confirmMenu->alignItemsVerticallyWithPadding(40);
  
  _topMenu->retain();
  _confirmMenu->retain();
  
  this->addChild(_topMenu);
  
}

PauseLayer::~PauseLayer() {
  _topMenu->release();
  _confirmMenu->release();
}

void PauseLayer::registerWithTouchDispatcher() {
  CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -1, true);
}

bool PauseLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
  return true;
}

void PauseLayer::onReplayPressed(CCObject* sender) {
}

void PauseLayer::onTitlePressed(CCObject* sender) {
}

void PauseLayer::onCancelPressed(CCObject* sender) {
  MainScene* scene = (MainScene*)this->getParent();
  scene->setPause(false);
  this->removeFromParentAndCleanup(true);
}

void PauseLayer::onYesPressed(CCObject* sender) {
}

void PauseLayer::onNoPressed(CCObject* sender) {
}