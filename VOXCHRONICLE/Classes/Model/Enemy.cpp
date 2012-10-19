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
  if (pobSprite && pobSprite->initWithScriptName(enemyName)) {
    pobSprite->autorelease();
    return pobSprite;
  }
  CC_SAFE_DELETE(pobSprite);
  return NULL;
}

Enemy* Enemy::initWithScriptName(const char* scriptName) {
  LuaObject* obj = new LuaObject(scriptName, "Enemy");
  obj->autorelease();
  _hp = obj->getInt("hp");
  _maxHP = _hp;
  _power = obj->getInt("power");
  _exp = obj->getInt("exp");
  _name = new string(obj->getString("name"));
  _counter = obj->getInt("counter");
  _speed = obj->getInt("speed");
  _type = (SkillType)obj->getInt("type");
  _level = obj->getInt("level");
  _speedCount = 0;
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
  this->setScale(this->getCurrentScale(_row));
  //this->setPosition(CCPointMake(60 + _col * 120, 40 + 35 * _row));
}

float Enemy::getRow() {
  return _row;
}

int Enemy::getCol() {
  return _col;
}

float Enemy::bottomLine() {
  return this->getPosition().y - this->getContentSize().height * this->getScale();
}

void Enemy::moveRow(float r) {
  this->setRow(this->getRow()  + r);
  this->getParent()->reorderChild(this, (MAX_ROW - _row));
}

DamageType Enemy::damage(Skill* skill, CharacterManager* characterManager) {
  const float tensions[] = {1.0, 1.5, 3.0, 4.5, 6};
  // ToDo 属性によるダメージ軽減とかもこの辺に載せてやる
  int damage = round(skill->getPower() * tensions[characterManager->getTension()]);
  DamageType type = DamageTypeHit;
  if (skill->getType() == SkillTypePhysical && this->getType() == SkillTypePhysical) {
    type = DamageTypePhysicalTolerant;
    damage *= 0.5;
  } else if (skill->getType() == SkillTypeMagical && this->getType() == SkillTypeMagical) {
    type = DamageTypeMagicalTolerant;
    damage *= 0.5;
  }
  float levelOffset = characterManager->getLevelOffsetRate(characterManager->getLevel(), this->getLevel());
  _hp -= round(damage * levelOffset);
  if (_hp <= 0) {
    type = DamageTypeDeath;
  }
  return type;
}

void Enemy::setLifeColor() {
  const float minColor = (0 * 255 + 244);
  //const float maxColor = (5 * 255 + 247);
  const float cast = 360.0 / (float)(255 * 6);
  ccColor3B color = HSVToColor3B((minColor + 150 * (_hp - 1)) * cast, 1, 1);
  this->cocos2d::CCSprite::setColor(color);
}

int Enemy::getExp() {
  return _exp;
}

void Enemy::setColAndRow(int col, float row) {
  int sx = 200 + 40 * col;
  int sy = 80 + 25 * (MAX_ROW - 1);
  int ex = 30 + 210 * col;
  int ey = 80;
  CCPoint sp = CCPointMake(sx, sy);
  CCPoint ep = CCPointMake(ex, ey);
  CCPoint sub = ccpSub(sp, ep);
  float scale = this->getCurrentScale(row);
  CCPoint p = ccpAdd(ep, ccpMult(sub, 1.0 - scale));
  this->setPosition(p);
  _row = row;
  _col = col;
}

float Enemy::getCurrentScale(float row) {
  int nr = (MAX_ROW - row);
  float sum = (float)(1 + MAX_ROW) * (float)MAX_ROW / 2.0;
  float tempSum = (float)(1 + nr) * (float)nr / 2.0;
  return 1.0 * tempSum / sum;
}

void Enemy::setRow(float r) {
  this->setColAndRow(this->getCol(), r);
}

void Enemy::setCol(int c) {
  this->setColAndRow(c, this->getRow());
}

int Enemy::getCounter() {
  return _counter;
}

int Enemy::getHP() {
  return _hp;
}

bool Enemy::canMove() {
  _speedCount = (_speedCount + 1) % _speed;
  return _speedCount == 0;
}

SkillType Enemy::getType() {
  return _type;
}

int Enemy::getLevel() {
  return _level;
}

