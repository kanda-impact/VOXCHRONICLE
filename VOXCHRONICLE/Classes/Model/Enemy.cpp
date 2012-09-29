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
  _hp = 1;
  _exp = 5;
  this->scheduleUpdate();
}

Enemy::~Enemy() {
}

void Enemy::update(float dt) {
  this->setLifeColor();
  this->setScale((float)(MAX_ROW - this->getRow()) / MAX_ROW);
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

bool Enemy::damage(int d) {
  _hp -= d;
  return (_hp <= 0);
}

void Enemy::setLifeColor() {
  ccColor3B colors[] = {
    ccc3(255, 241, 0),
    ccc3(174, 208, 61),
    ccc3(0, 167, 83),
    ccc3(0, 160, 180),
    ccc3(0, 100, 162),
    ccc3(30, 30, 140),
    ccc3(120, 20, 130),
    ccc3(230, 60, 140),
    ccc3(230, 0, 36)
  };
  int index = _hp;
  if (_hp > 8) index = 8;
  this->cocos2d::CCSprite::setColor(colors[index - 1]);
}

int Enemy::getExp() {
  return _exp;
}