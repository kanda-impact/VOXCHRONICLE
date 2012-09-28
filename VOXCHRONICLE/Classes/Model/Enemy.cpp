//
//  Enemy.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/28.
//
//

#include "Enemy.h"

Enemy* Enemy::create(const char *pszFileName) {
  Enemy *pobSprite = new Enemy();
  if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
    pobSprite->autorelease();
    return pobSprite;
    }
  CC_SAFE_DELETE(pobSprite);
  return NULL;
}

Enemy::Enemy() {
  _row = 7;
  _col = 0;
  _hp = 0;
  this->scheduleUpdate();
}

Enemy::~Enemy() {
}

void Enemy::update(float dt) {
  this->setColor(ccc3(255, 0, 0));
  this->setScale((float)(8 - this->getRow()) / 8.0);
  this->setPosition(CCPointMake(60 + _col * 120, 40 + 35 * _row));
}

float Enemy::getRow() {
  return _row;
}

void Enemy::setRow(float r) {
  _row = r;
}

int Enemy::getCol() {
  return _col;
}

void Enemy::setCol(int c) {
  _col = c;
}

float Enemy::bottomLine() {
  return this->getPosition().y - this->getContentSize().height * this->getScale();
}

void Enemy::moveRow(float r) {
  _row += r;
}