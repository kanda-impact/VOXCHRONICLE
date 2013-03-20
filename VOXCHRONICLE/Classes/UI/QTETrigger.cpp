//
//  QTETrigger.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/1/3.
//
//

#include "QTETrigger.h"
#include "BlinkLayer.h"
#include "FileUtils.h"

QTETrigger::QTETrigger(EnemyManager* manager) {
  _enemyManager = manager;
  _enemyManager->retain();
  CCSprite* buttonSprite = CCSprite::create("qte.png");
  CCSequence* seq = CCSequence::createWithTwoActions(CCFadeTo::create(0.5, 128), CCFadeTo::create(0.5, 255));
  buttonSprite->runAction(CCRepeatForever::create(seq));
  
  CCSprite* pressedSprite = CCSprite::create("qte_pressed.png");
  CCSprite* disableSprite = CCSprite::create("qte_pressed.png");
  
  CCMenuItemSprite* button = CCMenuItemSprite::create(buttonSprite,
                                                      pressedSprite,
                                                      disableSprite,
                                                      this,
                                                      menu_selector(QTETrigger::onButtonPressed));
  CCMenu* menu = CCMenu::create(button, NULL);
  CCDirector* director = CCDirector::sharedDirector();
  CCPoint center = CCPointMake(director->getWinSize().width / 2.0f, director->getWinSize().height / 2.0f);
  menu->setPosition(center);
  this->addChild(menu);
  _pressed = false;
}

QTETrigger::~QTETrigger() {
  _enemyManager->release();
}

void QTETrigger::onButtonPressed(CCObject* sender) {
  _pressed = true;
  CCMenuItemSprite* item = (CCMenuItemSprite*)sender;
  item->setEnabled(false);
  CCSprite* sprite = (CCSprite*)item->getNormalImage();
  sprite->setOpacity(1.0f);
  sprite->stopAllActions();
  BlinkLayer* bLayer = new BlinkLayer(ccc4(255, 255, 255, 255), 0.1f);
  bLayer->autorelease();
  _enemyManager->addChild(bLayer);
  
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/qte_decide.mp3").c_str());
  //this->getParent()->removeChild(this, true);
}

bool QTETrigger::isButtonPressed() {
  return _pressed;
}