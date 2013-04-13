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

CCArray* Enemy::_lifeColors = NULL;

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

void Enemy::loadLifeColors() {
  if (_lifeColors == NULL) {
    _lifeColors = CCArray::create();
    _lifeColors->retain();
    LuaObject* obj = LuaObject::create("enemy.lua");
    lua_State* L = obj->getLuaEngineWithLoad()->getLuaState();
    lua_getglobal(L, "getColors");
    if ( lua_isfunction(L, lua_gettop(L))) {
      lua_pushinteger(L, 300);
      if (lua_pcall(L, 1, 1, 0)) {
        cout << lua_tostring(L, lua_gettop(L)) << endl;
      }
      CCLuaValueArray* colorArray = obj->getArray();
      for (CCLuaValueArrayIterator it = colorArray->begin(); it != colorArray->end(); ++it) {
        CCArray* c = CCArray::create();
        CCLuaValueDict colors = it->dictValue();
        c->addObject(CCInteger::create(colors["1"].floatValue()));
        c->addObject(CCInteger::create(colors["2"].floatValue()));
        c->addObject(CCInteger::create(colors["3"].floatValue()));
        _lifeColors->addObject(c);
      }
    }
  }
}

Enemy* Enemy::create(const char *enemyName) {
  Enemy *pobSprite = new Enemy();
  if (pobSprite && pobSprite->initWithScriptName(enemyName)) {
    pobSprite->autorelease();
    return pobSprite;
  }
  CC_SAFE_DELETE(pobSprite);
  return NULL;
}

Enemy* Enemy::createWithSpecies(const char *speciesName) {
  Enemy *pobSprite = new Enemy();
  if (pobSprite && pobSprite->initWithSpecies(speciesName)) {
    pobSprite->autorelease();
    return pobSprite;
  }
  CC_SAFE_DELETE(pobSprite);
  return NULL;
}

Enemy* Enemy::initWithScriptName(const char* scriptName) {
  stringstream file;
  file << "Script/enemies/" << scriptName;
  _identifier = scriptName;
  _scriptPath = file.str();
  _register = new map<string, int>();
  _lua = new LuaObject(file.str().c_str());
  _maxHP = _lua->getInt("hp");
  _hp = _maxHP;
  _species = Species::getSpecies(_lua->getString("species"));
  _species->retain();
  _type = (SkillType)_lua->getInt("type");
  _level = _lua->getInt("level");
  _frequencyCount = 0;
  _enable = true;
  _movable = true;
  _counter = -1;
  _exp = this->getExpFromLua();
  _attack = _lua->getInt("attack");
  _frameSprite = NULL;
  stringstream ss;
  ss << _species->getImageName().c_str();
  _sheet = CCTextureCache::sharedTextureCache()->addImage(ss.str().c_str());
  _sheet->retain();
  _enemySize = _species->getEnemySize();
  if (_enemySize.width == 0 || _enemySize.height == 0) {
    int width = _sheet->getContentSize().width / _species->getAnimationFrames();
    _enemySize = CCSizeMake(width, width);
  }
  bool success = (bool)this->initWithTexture(_sheet, CCRectMake(0, 0,
                                                                _enemySize.width,
                                                                _enemySize.height));
  
  this->setLifeColor();
  this->setItem((EnemyItem)_lua->getInt("item"));
  if (success) {
    setDefaultAnimationClip();
    this->setScale(0.0f);
    return this;
  }
  return NULL;
}

Enemy* Enemy::initWithSpecies(const char* speciesName) {
  stringstream file;
  file << "Script/enemies/" << speciesName;
  _identifier = speciesName;
  _scriptPath = file.str();
  _register = new map<string, int>();
  _lua = NULL;
  _maxHP = 1;
  _hp = _maxHP;
  _species = Species::getSpecies(speciesName);
  _species->retain();
  _type = SkillTypeNormal;
  _level = 1;
  _frequencyCount = 0;
  _enable = true;
  _movable = true;
  _counter = -1;
  if (_lua) {
    _exp = this->getExpFromLua();
  } else {
    _exp = 0;
  }
  _attack = 0;
  _frameSprite = NULL;
  stringstream ss;
  ss << _species->getImageName().c_str();
  _sheet = CCTextureCache::sharedTextureCache()->addImage(ss.str().c_str());
  _sheet->retain();
  _enemySize = _species->getEnemySize();
  if (_enemySize.width == 0 || _enemySize.height == 0) {
    int width = _sheet->getContentSize().width / _species->getAnimationFrames();
    _enemySize = CCSizeMake(width, width);
  }
  bool success = (bool)this->initWithTexture(_sheet, CCRectMake(0, 0,
                                                                _enemySize.width,
                                                                _enemySize.height));
  
  this->setLifeColor();
  this->setItem(EnemyItemNone);
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
  if (_lua) {
    _lua->release();
  }
  _species->release();
  _sheet->release();
  CCLog("enemy %s is released", this->getIdentifier().c_str());
}

void Enemy::update(float dt) {
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

int Enemy::damage(int power, Skill* skill, CharacterManager* characterManager, DamageType& damageType, bool simulate) {
  float damage = floor(0.5 + power);
  
  // 無効化の処理
  if (!this->getSpecies()->isEnableSkill(skill)) {
    damageType = DamageTypeDisable;
    return 0;
  }
  
  // アイテムの処理
  if (skill->getPower(characterManager) == 0) { // そもそもダメージが通らないとき
    damageType = DamageTypeNoDamage;
    damage = 0;
    return damage;
  } else if ((_item == EnemyItemShield && skill->getType() == SkillTypePhysical) ||
      (_item == EnemyItemBarrier && skill->getType() == SkillTypeMagical)) {
    // 盾によって完全に無効化されている状態
    damage = 0;
    damageType = _item == EnemyItemShield ? DamageTypePhysicalInvalid : DamageTypeMagicalInvalid;
    return damage;
  } else if ((_item == EnemyItemShield && skill->getType() == SkillTypeMagical) ||
             (_item == EnemyItemBarrier && skill->getType() == SkillTypePhysical)) {
    damage = 0;
    if (!simulate) { // simulateがfalseのときだけ、アイテムを消去してやる
      this->setItem(EnemyItemNone);
    }
    damageType = _item == EnemyItemShield ? DamageTypeShieldBreak : DamageTypeBarrierBreak;
    return damage;
  }
  
  damageType = DamageTypeHit;
  // ダメージ耐性がある場合、威力半減してやる
  if (skill->getType() == SkillTypePhysical && this->getType() == SkillTypePhysical) {
    damageType = DamageTypePhysicalResist;
    damage *= 0.5;
  } else if (skill->getType() == SkillTypeMagical && this->getType() == SkillTypeMagical) {
    damageType = DamageTypeMagicalResist;
    damage *= 0.5;
  }
  // レベル補正を行います
  //float levelOffset = characterManager->getLevelOffsetRate(characterManager->getLevel(), this->getLevel());
  //damage = floor(0.5 + damage * levelOffset);
  int hp = this->getHP();
  hp -= damage;
  if (hp <= 0) {
    // ダメージが原因で死んだら死亡
    damageType = DamageTypeDeath;
    hp = 0;
  } else if (damage == 0){
    // ダメージが当たらなかったら無敵
    damageType = DamageTypeInvincible;
  } else if (damage < 0) {
    // ダメージがマイナス値なら吸収
    damageType = DamageTypeAbsorption;
  }
  if (!simulate) { // simulateがfalseのとき、実際にダメージを与えます
    _hp = hp;
    if (damage != 0) {
      this->setLifeColor(); // モンスターの色を更新
    }
  }
  return damage;
}

void Enemy::setLifeColor() {
  CCArray* color = NULL;
  if (_hp < _lifeColors->count()) {
    color = (CCArray*)_lifeColors->objectAtIndex(_hp);
  } else {
    color = (CCArray*)_lifeColors->lastObject();
  }
  int r = ((CCInteger*)color->objectAtIndex(0))->getValue();
  int g = ((CCInteger*)color->objectAtIndex(1))->getValue();
  int b = ((CCInteger*)color->objectAtIndex(2))->getValue();
  ccColor3B c = ccc3(r, g, b);
  this->setColor(c);
}

int Enemy::getExpFromLua() {
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
  return defaultExp;
}

int Enemy::getExp() {
  return _exp;
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
  this->toggleBlink(row == 0);
  _row = row;
  _col = col;
  if (_row > 0) {
    this->setOpacity(255);
  }
}

float Enemy::getCurrentScale(float row) {
  return EnemyManager::calcScale(row);
}

void Enemy::setRow(float r) {
  this->setRowAndCol(r, this->getCol());
}

void Enemy::setCol(int c) {
  this->setRowAndCol(this->getRow(), c);
}

int Enemy::getCounter() {
  // スクリプト側でリフを自由に変えられるように
  // _counterが-の時は種族の持つデフォのリフ番号を返し、
  // そうじゃない場合は登録されたリフ番号が返ります
  if (_counter < 0) {
    return _species->getCounter();
  }
  return _counter;
}

void Enemy::setCounter(int counter) {
  _counter = counter;
}

int Enemy::getHP() {
  return _hp;
}

void Enemy::setHP(int hp) {
  _hp = hp;
}

bool Enemy::canMove(CharacterManager* manager) {
  _frequencyCount = (_frequencyCount + 1) % this->getFrequency(manager);
  return _frequencyCount == 0;
}

SkillType Enemy::getType() {
  return _type;
}

int Enemy::getLevel() {
  return _level;
}

int Enemy::getAttack() {
  if (_attack != 0) {
    return _attack;
  }
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
  CCPoint point = CCPointZero;
  if (item != EnemyItemNone) {
    string filename;
    CCSprite* sprite = NULL;
    if (item == EnemyItemShield) {
      filename = "Image/shield.png";
      sprite = CCSprite::create(FileUtils::getFilePath(filename.c_str()).c_str());
      sprite->setColor(VOX_COLOR);
      sprite->setScale(1.0f);
    } else if (item == EnemyItemBarrier) {
      filename = "Image/barrier.png";
      sprite = CCSprite::create(FileUtils::getFilePath(filename.c_str()).c_str());
      sprite->setColor(LSK_COLOR);
      sprite->setScale(2.0f);
    }
    point = ccp(this->getContentSize().width / 2.0f, this->getContentSize().height / 2.0f);
    sprite->setOpacity(164);
    this->addChild(sprite, 1000, EnemyTagItem);
    sprite->setPosition(point);
  }
}

bool Enemy::performSkill(CharacterManager* characterManager, EnemyManager* enemyManager) {
  string skillName = _species->choiceEnemySkill(this, characterManager, enemyManager);
  if (skillName.size() == 0) return false; // 技の名前が何か返ってきたとき、その技を生成して実行してやる
  EnemySkill* skill = new EnemySkill(skillName.c_str());
  skill->performSkill(this, characterManager, enemyManager);
  return true;
}

bool Enemy::setAnimationClip(const char *clipName, int frames, bool hasFrame) {
  string name = string(clipName);
  int xOffset = 0;
  if (name == "attack") {
    xOffset = 0;
  } else if (name == "death") {
    xOffset = 1;
  }
  return this->setAnimationAndFrame(xOffset, 2, frames, hasFrame);
}

bool Enemy::setDefaultAnimationClip() {
  return this->setAnimationAndFrame(0, 0, _species->getAnimationFrames(), _species->hasFrame());
}

bool Enemy::setAnimationAndFrame(int xOffset, int yOffset, int frames, bool hasFrame) {
  this->stopAllActions(); // 全てのアニメーションを停止
  if (this->getChildByTag(EnemyTagFrame) != NULL) {
    this->removeChildByTag(EnemyTagFrame, true); // フレームを取る
  }
  stringstream ss;
  bool success = _sheet != NULL;
  
  if (success) {
    int width = _enemySize.width;
    int height = _enemySize.height;
    CCAnimation* animation = CCAnimation::create();
    for (int i = 0; i < frames; ++i) {
      CCSpriteFrame* frame = CCSpriteFrame::createWithTexture(_sheet, CCRectMake(xOffset * width + width * i, yOffset * height, width, height));
      animation->addSpriteFrame(frame);
    }
    animation->setLoops(-1);
    animation->setDelayPerUnit(10.0 / 60.0);
    this->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
    // もし、フレームを持っているなら、フレームを追加してやる
    if (hasFrame) {
      CCSprite* frameSprite = this->createFrameSprite(xOffset, yOffset + 1, frames);
      frameSprite->setAnchorPoint(ccp(0, 0));
      this->setFrameColor(frameSprite, _type);
      this->addChild(frameSprite, EnemyLayerFrame, EnemyTagFrame);
      if (_frameSprite) {
        _frameSprite->release();
        _frameSprite = NULL;
      }
      _frameSprite = frameSprite;
      _frameSprite->retain();
    }
    return true;
  }
  return false;
}

CCSprite* Enemy::createFrameSprite(int xOffset, int yOffset, int frames) {
  int width = _enemySize.width;
  int height = _enemySize.height;
  CCSprite* frame = CCSprite::createWithTexture(_sheet, CCRectMake(xOffset * width, yOffset * height, width, height));
  CCAnimation* animation = CCAnimation::create();
  for (int i = 0; i < frames; ++i) {
    CCSpriteFrame* frame = CCSpriteFrame::createWithTexture(_sheet, CCRectMake(xOffset * width + width * i, yOffset * height, width, height));
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

int Enemy::getSpeed(CharacterManager* manager) {
  LuaObject* lua = _species->getLuaObject();
  lua_State* L = lua->getLuaEngineWithLoad()->getLuaState();
  lua_getfield(L, lua_gettop(L), "getSpeed");
  if (lua_isfunction(L, lua_gettop(L))) {
    _lua->pushCCObject(this, "Enemy");
    _lua->pushCCObject(manager, "CharacterManager");
    if (lua_pcall(L, 2, 1, 0)) {
      cout << lua_tostring(L, lua_gettop(L)) << endl;
    }
    return lua_tointeger(L, lua_gettop(L));
  }
  return 0;
}

int Enemy::getFrequency(CharacterManager* manager) {
  LuaObject* lua = _species->getLuaObject();
  lua_State* L = lua->getLuaEngineWithLoad()->getLuaState();
  lua_getfield(L, lua_gettop(L), "getFrequency");
  if (lua_isfunction(L, lua_gettop(L))) {
    _lua->pushCCObject(this, "Enemy");
    _lua->pushCCObject(manager, "CharacterManager");
    if (lua_pcall(L, 2, 1, 0)) {
      cout << lua_tostring(L, lua_gettop(L)) << endl;
    }
    return lua_tointeger(L, lua_gettop(L));
  }
  return 1;
}

Species* Enemy::getSpecies() {
  return _species;
}

string Enemy::getIdentifier() {
  return _identifier;
}

void Enemy::setSilhouette() {
  this->stopAllActions();
  this->setColor(ccc3(5, 5, 5));
  
  if (_frameSprite) {
    _frameSprite->stopAllActions();
    _frameSprite->setColor(ccc3(5, 5, 5));
  }
}

void Enemy::setSkillType(SkillType type) {
  _type = type;
  if (_frameSprite) {
    this->setFrameColor(_frameSprite, type);
  }
}

void Enemy::setFrameColor(cocos2d::CCSprite *frameSprite, SkillType type) {
  ccColor3B color = ccc3(0, 0, 0);
  if (type == SkillTypeNormal || type == SkillTypeNone) {
    frameSprite->setColor(color);
  } else {
    if (type == SkillTypeMagical) {
      color = LSK_COLOR;
    } else {
      color = ccc3(0, 255, 230);
    }
    frameSprite->setColor(ccc3(0, 0, 0));
    CCRepeatForever* blink = CCRepeatForever::create(CCSequence::createWithTwoActions(CCTintTo::create(0.5, color.r, color.g, color.b),
                                                                                      CCTintTo::create(1.0, 0, 0, 0)));
    frameSprite->runAction(blink);
    frameSprite->setColor(color);
  }
}

int Enemy::getMaxHP() {
  return _maxHP;
}