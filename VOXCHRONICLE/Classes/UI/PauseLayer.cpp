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

PauseLayer::PauseLayer(MainScene* main) : GameOverLayer(main) {
  this->buildUI();
}

void PauseLayer::buildUI() {
  this->removeAllChildrenWithCleanup(true);
  _state = PauseLayerStateTop;
  
  this->setTouchEnabled(true);
  
  CCDirector* director = CCDirector::sharedDirector();
  
  CCLayerColor* background = CCLayerColor::create(ccc4(0, 0, 0, 128), director->getWinSize().width, director->getWinSize().height);
  this->addChild(background);
  
  CCSprite* pause = CCSprite::create("pause_label.png");
  pause->setPosition(ccp(director->getWinSize().width / 2.0, 250));
  this->addChild(pause);
  
  _topMenu = CCMenu::create(CCMenuItemImage::create("resume.png", "resume_pressed.png", this, menu_selector(PauseLayer::onCancelPressed)),
                            CCMenuItemImage::create("replay.png", "replay_pressed.png", this, menu_selector(PauseLayer::onReplayPressed)),
                            CCMenuItemImage::create("title.png", "title_pressed.png", this, menu_selector(PauseLayer::onTitlePressed)),
                            NULL);
  
  _confirmMenu = CCMenu::create(CCMenuItemImage::create("yes.png", "yes_pressed.png",
                                                        this, menu_selector(PauseLayer::onYesPressed)),
                                CCMenuItemImage::create("no.png", "no_pressed.png",
                                                        this, menu_selector(PauseLayer::onNoPressed)),
                                NULL);
  _topMenu->setPosition(ccp(director->getWinSize().width / 2.0, 140));
  _confirmMenu->setPosition(ccp(director->getWinSize().width / 2.0, 140));
  _topMenu->alignItemsVerticallyWithPadding(20);
  _topMenu->setAnchorPoint(ccp(0.5, 0.5));
  _confirmMenu->setAnchorPoint(ccp(0.5, 0.5));
  _confirmMenu->alignItemsVerticallyWithPadding(20);
  
  _descriptionLabel = CCLabelTTF::create("ゲームを中断します。よろしいですか？", FONT_NAME, 16);
  _descriptionLabel->setPosition(ccp(director->getWinSize().width / 2.0, 200));
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
  scene->release();
}

void PauseLayer::onYesPressed(CCObject* sender) {
  MainScene* scene = (MainScene*)this->getParent();
  scene->setPause(false);
  this->removeFromParentAndCleanup(true);
  if (_state == PauseLayerStateConfirmReplay) {
    this->replayButtonPressed(NULL);
    scene->release();
  } else if (_state == PauseLayerStateConfirmTitle) {
    this->titleButtonPressed(NULL);
    scene->release();
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