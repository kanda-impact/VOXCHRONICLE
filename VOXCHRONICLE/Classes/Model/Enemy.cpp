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
  _hp = _lua->getInt("hp");
  _species = new Species(_lua->getString("species"));
  _species->retain();
  _maxHP = _hp;
  _type = (SkillType)_lua->getInt("type");
  _level = _lua->getInt("level");
  _speedCount = 0;
  _enable = true;
  _movable = true;
  stringstream ss;
  ss << "Image/" << _species->getImageName().c_str() << "0.png";
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
  this->scheduleUpdate();
}

Enemy::~Enemy() {
  _lua->release();
  _species->release();
  delete _register;
  cout << "Enemy was released." << endl;
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
  //this->getParent()->reorderChild(this, (MAX_ROW - _row));
}

DamageType Enemy::damage(Skill* skill, CharacterManager* characterManager, bool simulate) {
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
    if (!simulate) { // simulateがfalseのときだけ、アイテムを消去してやる
      this->setItem(EnemyItemNone);
    }
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
  int hp = this->getHP();
  hp -= damage;
  if (hp <= 0) {
    // ダメージが原因で死んだら死亡
    type = DamageTypeDeath;
    hp = 0;
  } else if (damage == 0){
    // ダメージが当たらなかったら無敵
    type = DamageTypeInvincible;
  } else if (damage < 0) {
    // ダメージがマイナス値なら吸収
    type = DamageTypeAbsorption;
  }
  if (!simulate) { // simulateがfalseのとき、実際にダメージを与えます
    _hp = hp;
  }
  return type;
}

void Enemy::setLifeColor() {
  const float minColor = (0 * 255 + 244);
  //const float maxColor = (5 * 255 + 247);
  const float cast = 360.0 / (float)(255 * 6);
  ccColor3B color = HSVToColor3B((minColor + 200 * (_hp - 1)) * cast, 1, 1);
  this->cocos2d::CCSprite::setColor(color);
}

int Enemy::getExp() {
  int defaultExp = _species->getDefaultExp(_level, _maxHP, _item, _type);
  lua_State* L = _lua->getLuaEngineWithLoad()->getLuaState();
  lua_getfield(L, lua_gettop(L), "getExp");
  if (lua_isfunction(L, lua_gettop(L))) {
    lua_pushinteger(L, defaultExp);
    if (lua_pcall(L, 1, 1, 0)) {
      cout << lua_tostring(L, lua_gettop(L)) << endl;
    }
    int exp = lua_tonumber(L, lua_gettop(L));
    return exp;
  }
  return 0;
 
}

void Enemy::setRowAndCol(int row, float col) {
  CCPoint p = EnemyManager::calcLinePosition(row, col);
  this->setPosition(ccp(p.x, p.y));
  this->setAnchorPoint(ccp(0.5f, 0.0f));
  // 並び順の変更
  CCNode* parent = this->getParent();
  if (parent != NULL) {
    parent->removeChild(this, false);
    int order = (MAX_ROW - row) * 10 + (3 - col);
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
  return _species->getCounter();
}

int Enemy::getHP() {
  return _hp;
}

bool Enemy::canMove() {
  _speedCount = (_speedCount + 1) % _species->getSpeed();
  return _speedCount == 0 && this->getRow() >= _species->getMinRow() && this->isMovable();
}

SkillType Enemy::getType() {
  return _type;
}

int Enemy::getLevel() {
  return _level;
}

int Enemy::getAttack() {
  return _species->getAttack();
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
  string skillName = _species->choiceEnemySkill(this);
  if (skillName.size() == 0) return false; // 技の名前が何か返ってきたとき、その技を生成して実行してやる
  EnemySkill* skill = new EnemySkill(skillName.c_str());
  skill->performSkill(this, characterManager, enemyManager);
  return true;
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
  ss << _species->getImageName() << "_" << clipName;
  return this->setAnimationAndFrame(ss.str().c_str(), frames, hasFrame);
}

bool Enemy::setDefaultAnimationClip() {
  return this->setAnimationAndFrame(_species->getImageName().c_str(), _species->getAnimationFrames(), _species->hasFrame());
}

bool Enemy::setAnimationAndFrame(const char *filePrefix, int frames, bool hasFrame) {
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

string Enemy::getName() {
  return _species->getName();
}

bool Enemy::isMovable() {
  return _movable;
}

void Enemy::setMovable(bool m) {
  _movable = m;
}
