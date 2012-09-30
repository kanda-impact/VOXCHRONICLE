//
//  Enemy.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/28.
//
//

#include <sstream>
#include "Enemy.h"
#include "LuaObject.h"

using namespace std;

Enemy* Enemy::create(const char *enemyName) {
  Enemy *pobSprite = new Enemy();
  stringstream ss;
  ss << enemyName << ".lua";
  if (pobSprite && pobSprite->initWithScriptName(ss.str().c_str())) {
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
  _exp = 0;
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
  this->getParent()->reorderChild(this, (MAX_ROW - _row));
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

Enemy* Enemy::initWithScriptName(const char* scriptName) {
  LuaObject* obj = new LuaObject(scriptName, "Enemy");
  _hp = obj->getInt("hp");
  _power = obj->getInt("power");
  _exp = obj->getInt("exp");
  _name = obj->getString("name");
  const char* imageName = obj->getString("imageName");
  int frameCount = obj->getInt("animationFrames");
  stringstream ss;
  ss << imageName << "0.png";
  bool success = (bool)this->initWithFile(ss.str().c_str());
  if (success) {
    CCAnimation* animation = CCAnimation::create();
    CCSize size = this->getTexture()->getContentSize();
    for (int i = 0; i < frameCount; ++i) {
      stringstream frameSS;
      frameSS << imageName << i << ".png";
      CCSpriteFrame* frame = CCSpriteFrame::create(frameSS.str().c_str(), CCRectMake(0, 0, size.width, size.height));
      animation->addSpriteFrame(frame);
    }
    animation->setLoops(-1);
    animation->setDelayPerUnit(10.0 / 60.0);
    this->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
    delete obj;
    return this;
  }
  return NULL;
}