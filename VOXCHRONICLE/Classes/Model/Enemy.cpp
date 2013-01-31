//
//  Enemy.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/28.
//
//

#include <sstream>
#include <cmath>
#include "Enemy.h"
#include "LuaObject.h"
#include "Utils.h"
#include "FileUtils.h"
#include "macros.h"
#include "EnemySkill.h"

using namespace std;

enum { // 深度
  EnemyLayerFrame = 1,
  EnemyLayerItem = 2
};

enum { // タグ
  EnemyTagFrame = 1,
  EnemyTagItem = 2
};

enum { // アニメーションタグ
  EnemyAnimationTagBlink = 1
};

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
  stringstream file;
  file << "Script/enemies/" << scriptName;
  _scriptPath = file.str();
  _register = new map<string, int>();
  _lua = new LuaObject(file.str().c_str());
  _lua->retain();
  _hp = _lua->getInt("hp");
  _maxHP = _hp;
  _attack = _lua->getInt("attack");
  _exp = _lua->getInt("exp");
  _name = new string(_lua->getString("name"));
  _counter = _lua->getInt("counter");
  _speed = _lua->getInt("speed");
  _type = (SkillType)_lua->getInt("type");
  _level = _lua->getInt("level");
  _minRow = _lua->getInt("minRow");
  _hasFrame = _lua->getBoolean("hasFrame");
  _speedCount = 0;
  _imageName = _lua->getString("imageName");
  _frameCount = _lua->getInt("animationFrames");
  _enable = true;
  stringstream ss;
  ss << "Image/" << _imageName << "0.png";
  bool success = (bool)this->initWithFile(FileUtils::getFilePath(ss.str().c_str()).c_str());
  this->setItem((EnemyItem)_lua->getInt("item"));
  if (success) {
    setDefaultAnimationClip();
    this->setScale(0.0f);
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
  _lua->release();
  delete _name;
  delete _register;
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
  // ToDo 属性によるダメージ軽減とかもこの辺に載せてやる
  float damage = floor(0.5 + skill->getPowerWithTension(characterManager->getTension()));
  
  // アイテムの処理
  if ((_item == EnemyItemShield && skill->getType() == SkillTypePhysical) ||
      (_item == EnemyItemBarrier && skill->getType() == SkillTypeMagical)) {
    // 盾によって完全に無効化されている状態
    damage = 0;
    return _item == EnemyItemShield ? DamageTypePhysicalInvalid : DamageTypeMagicalInvalid;
  } else if ((_item == EnemyItemShield && skill->getType() == SkillTypeMagical) ||
             (_item == EnemyItemBarrier && skill->getType() == SkillTypePhysical)) {
    damage = 0;
    this->setItem(EnemyItemNone);
    return _item == EnemyItemShield ? DamageTypeShieldBreak : DamageTypeBarrierBreak;
  }
  
  DamageType type = DamageTypeHit;
  // ダメージ耐性がある場合、威力半減してやる
  if (skill->getType() == SkillTypePhysical && this->getType() == SkillTypePhysical) {
    type = DamageTypePhysicalResist;
    damage *= 0.5;
  } else if (skill->getType() == SkillTypeMagical && this->getType() == SkillTypeMagical) {
    type = DamageTypeMagicalResist;
    damage *= 0.5;
  }
  // レベル補正を行います
  float levelOffset = characterManager->getLevelOffsetRate(characterManager->getLevel(), this->getLevel());
  damage = floor(0.5 + damage * levelOffset);
  _hp -= damage;
  if (_hp <= 0) {
    // ダメージが原因で死んだら死亡
    type = DamageTypeDeath;
  } else if (damage == 0){
    // ダメージが当たらなかったら無敵
    type = DamageTypeInvincible;
  } else if (damage < 0) {
    // ダメージがマイナス値なら吸収
    type = DamageTypeAbsorption;
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

void Enemy::setRowAndCol(int row, float col) {
  CCPoint root = CCPointZero;
  CCPoint end = CCPointZero;
  const int width = 480;
  const int horizonWidth = 120;
  const int horizonDistance = 122.5;
  const int marginLeft = (width - horizonWidth) / 2.0f;
  const int padding = 50;
  const float scale = horizonWidth / width;
  if (col == 0) {
    root = ccp(padding, 0);
    end = ccp(marginLeft + padding * scale, horizonDistance);
  } else if (col == 1) {
    root = ccp(width / 2.0, 0);
    end = ccp(width / 2.0, horizonDistance);
  } else if (col == 2) {
    root = ccp(width - padding, 0);
    end = ccp(marginLeft + horizonWidth - padding * scale, horizonDistance);
  }
  CCPoint sub = ccpSub(end, root);
  CCPoint p = ccpAdd(root, ccpMult(sub, row / (float)MAX_ROW));
  this->setPosition(p);
  this->setAnchorPoint(ccp(0.5f, 0.0f));
  // 並び順の変更
  CCNode* parent = this->getParent();
  if (parent != NULL) {
    parent->removeChild(this, false);
    int order = (MAX_ROW - row) * 10;
    parent->addChild(this, order);
  }
  this->toggleBlink(row <= 1);
  _row = row;
  _col = col;
}

float Enemy::getCurrentScale(float row) {
  return (0.108f * MAX_ROW) - (0.108f * row);
}

void Enemy::setRow(float r) {
  this->setRowAndCol(r, this->getCol());
}

void Enemy::setCol(int c) {
  this->setRowAndCol(this->getRow(), c);
}

int Enemy::getCounter() {
  return _counter;
}

int Enemy::getHP() {
  return _hp;
}

bool Enemy::canMove() {
  _speedCount = (_speedCount + 1) % _speed;
  return _speedCount == 0 && this->getRow() >= _minRow;
}

SkillType Enemy::getType() {
  return _type;
}

int Enemy::getLevel() {
  return _level;
}

int Enemy::getAttack() {
  return _attack;
}

EnemyItem Enemy::getItem() {
  return _item;
}

void Enemy::setItem(EnemyItem item) {
  if (item == _item) return;
  if (_item != EnemyItemNone && this->getChildByTag(EnemyTagItem)) {
    this->removeChildByTag(EnemyTagItem, true);
  }
  _item = item;
  if (item != EnemyItemNone) {
    const char* filename;
    CCSprite* sprite = NULL;
    if (item == EnemyItemShield) {
      filename = "Image/shield.png";
      sprite = CCSprite::create(FileUtils::getFilePath(filename).c_str());
      sprite->setColor(VOX_COLOR);
    } else if (item == EnemyItemBarrier) {
      filename = "Image/barrier.png";
      sprite = CCSprite::create(FileUtils::getFilePath(filename).c_str());
      sprite->setColor(LSK_COLOR);
    }
    this->addChild(sprite, 1000, EnemyTagItem);
  }
}

bool Enemy::performSkill(CharacterManager* characterManager, EnemyManager* enemyManager) {
  lua_State* L = _lua->getLuaEngine()->getLuaState();
  lua_getglobal(L, "Enemy");
  lua_getfield(L, lua_gettop(L), "performSkill");
  if (lua_isfunction(L, lua_gettop(L))) {
    _lua->pushCCObject(this, "Enemy");
    if (lua_pcall(L, 1, 1, 0)) {
      cout << lua_tostring(L, lua_gettop(L)) << endl;
      return false;
    }
    string skillName = lua_tostring(L, lua_gettop(L));
    if (skillName.size() == 0) return false;
    // 技の名前が何か帰ってきたとき、その技を生成して実行してやる
    EnemySkill* skill = new EnemySkill(skillName.c_str());
    skill->performSkill(this, characterManager, enemyManager);
    return true;
  }
  return false;
}

int Enemy::getRegister(const char *key, int defaultValue) {
  if (this->hasRegister(key)) {
    return _register->at(key);
  }
  return defaultValue;
}

void Enemy::setRegister(const char *key, int value) {
  if (this->hasRegister(key)) {
    (*_register)[string(key)] = value;
  } else {
    _register->insert(std::pair<string, int>(string(key), value));
  }
}

bool Enemy::hasRegister(const char *key) {
  return _register->count(key) == 1;
}

bool Enemy::setAnimationClip(const char *clipName, int frames, bool hasFrame) {
  stringstream ss;
  ss << _imageName << "_" << clipName;
  return this->setAnimatonAndFrame(ss.str().c_str(), frames, hasFrame);
}

bool Enemy::setDefaultAnimationClip() {
  return this->setAnimatonAndFrame(_imageName, _frameCount, _hasFrame);
}

bool Enemy::setAnimatonAndFrame(const char *filePrefix, int frames, bool hasFrame) {
  this->stopAllActions(); // 全てのアニメーションを停止
  if (this->getChildByTag(EnemyTagFrame) != NULL) {
    this->removeChildByTag(EnemyTagFrame, true); // フレームを取る
  }
  stringstream ss;
  ss << "Image/" << filePrefix << "0.png";
  CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(FileUtils::getFilePath(ss.str().c_str()).c_str());
  bool success = texture != NULL;
  this->setTexture(texture);
  if (success) {
    CCAnimation* animation = CCAnimation::create();
    CCSize size = this->getTexture()->getContentSize();
    for (int i = 0; i < frames; ++i) {
      stringstream frameSS;
      frameSS << "Image/" << filePrefix << i << ".png";
      CCSpriteFrame* frame = CCSpriteFrame::create(FileUtils::getFilePath(frameSS.str().c_str()).c_str(), CCRectMake(0, 0, size.width, size.height));
      animation->addSpriteFrame(frame);
    }
    animation->setLoops(-1);
    animation->setDelayPerUnit(10.0 / 60.0);
    this->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
    
    // もし、フレームを持っているなら、フレームを追加してやる
    if (hasFrame) {
      CCSprite* frameSprite = this->createFrameSprite(filePrefix, frames);
      frameSprite->setAnchorPoint(ccp(0, 0));
      if (_type == SkillTypePhysical) {
        frameSprite->setColor(VOX_COLOR);
      } else if (_type == SkillTypeMagical) {
        frameSprite->setColor(LSK_COLOR);
      } else {
        frameSprite->setColor(ccc3(0, 0, 0));
      }
      this->addChild(frameSprite, EnemyLayerFrame, EnemyTagFrame);
    }
    return true;
  }
  return false;
}

CCSprite* Enemy::createFrameSprite(const char* filePrefix, int frames) {
  stringstream ss;
  ss << "Image/" << "w_" << filePrefix << 0 << ".png";
  CCSprite* frame = CCSprite::create(FileUtils::getFilePath(ss.str().c_str()).c_str());
  CCAnimation* animation = CCAnimation::create();
  CCSize size = this->getTexture()->getContentSize();
  for (int i = 0; i < frames; ++i) {
    stringstream frameSS;
    frameSS << "Image/" << "w_" << filePrefix << i << ".png";
    CCSpriteFrame* frame = CCSpriteFrame::create(FileUtils::getFilePath(frameSS.str().c_str()).c_str(), CCRectMake(0, 0, size.width, size.height));
    animation->addSpriteFrame(frame);
  }
  animation->setLoops(-1);
  animation->setDelayPerUnit(10.0 / 60.0);
  frame->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
  return frame;
}

bool Enemy::getEnable() {
  return _enable;
}

void Enemy::setEnable(bool enable) {
  _enable = enable;
}

void Enemy::toggleBlink(bool toggle) {
  if (toggle) {
    CCRepeatForever* blink = CCRepeatForever::create(CCSequence::createWithTwoActions(CCFadeTo::create(0.2, 127), CCFadeTo::create(0.2, 255)));
    blink->setTag(EnemyAnimationTagBlink);
    this->runAction(blink);
  } else {
    this->stopActionByTag(EnemyAnimationTagBlink);
  }
}

