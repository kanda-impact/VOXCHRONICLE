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
#include "Utils.h"

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
  _maxHP = _hp;
  _exp = 0;
  this->scheduleUpdate();
}

Enemy::~Enemy() {
  delete _name;
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
  const float maxColor = (5 * 255 + 247);
  const float minColor = (0 * 255 + 244);
  const float endColor = maxColor * ((float)_maxHP / 10.0);
  const float cast = 360.0 / (float)(255 * 6);
  float hpRate = (float)_hp / (float)_maxHP;
  ccColor3B color = HSVToColor3B((minColor + (endColor - minColor) * hpRate) * cast, 1, 1);
  this->cocos2d::CCSprite::setColor(color);
}

int Enemy::getExp() {
  return _exp;
}

Enemy* Enemy::initWithScriptName(const char* scriptName) {
  LuaObject* obj = new LuaObject(scriptName, "Enemy");
  obj->autorelease();
  _hp = obj->getInt("hp");
  _maxHP = _hp;
  _power = obj->getInt("power");
  _exp = obj->getInt("exp");
  _name = new string(obj->getString("name"));
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
    return this;
  }
  return NULL;
}