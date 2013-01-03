//
//  QTETrigger.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/1/3.
//
//

#include "QTETrigger.h"
#include "FileUtils.h"

QTETrigger::QTETrigger(EnemyManager* manager) {
  _enemyManager = manager;
  _enemyManager->retain();
  string fileName = FileUtils::getFilePath("Image/Main/UI/qte.png");
  CCMenuItemImage* button = CCMenuItemImage::create(fileName.c_str(), fileName.c_str(), this, menu_selector(QTETrigger::onButtonPressed));
  CCMenu* menu = CCMenu::create(button, NULL);
  CCDirector* director = CCDirector::sharedDirector();
  CCPoint center = CCPointMake(director->getWinSize().width / 2.0f, director->getWinSize().height / 2.0f);
  menu->setPosition(center);
  this->addChild(menu);
}

QTETrigger::~QTETrigger() {
  _enemyManager->release();
}

void QTETrigger::onButtonPressed() {
  _pressed = true;
  this->getParent()->removeChild(this, true);
}

bool QTETrigger::isButtonPressed() {
  return _pressed;
}