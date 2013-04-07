//
//  CharacterManager.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/28.
//
//

#include <sstream>
#include "FileUtils.h"
#include "CharacterManager.h"
#include "Skill.h"
#include "CCLuaEngine.h"
#include "SaveData.h"

CharacterManager::CharacterManager() {
  Character* vox = new Character("vox");
  vox->autorelease();
  
  Character* lsk = new Character("lsk");
  lsk->autorelease();
  
  _characters = CCArray::create(vox, lsk, NULL);
  _characters->retain();
  _currentCharacter = vox;
  _repeatCount = 0;
  _repeatCountRaw = 0;
  _waitTurn = 0;
  _currentSkill = NULL;
  _lastSkill = NULL;
  _tension = 0;
  _exp = 0;
  _shield = false;
  _maxHP = 0;
  _maxMP = 0;
  _isExpDirty = true;
  this->updateParameters();
  _hp = _maxHP;
  _mp = _maxMP;
  _drumLevel = 0;
  _damageInfoQueue = new std::queue<DamageInfo>();
}

CharacterManager::~CharacterManager() {
  _characters->release();
  delete _damageInfoQueue;
  if (_lastSkill) _lastSkill->release();
  if (_currentSkill) _currentSkill->release();
}

Character* CharacterManager::getCurrentCharacter() {
  return _currentCharacter;
}

bool CharacterManager::isPerforming() {
  return (_currentSkill && _waitTurn < _currentSkill->getTurn());
}

void CharacterManager::setLastSkill(Skill* skill) {
  if (_lastSkill) {
    _lastSkill->release();
  }
  if (skill) {
    skill->retain();
  }
  _lastSkill = skill;
}

void CharacterManager::setCurrentSkill(Skill* skill) {
  if (_currentSkill) {
    _currentSkill->release();
  }
  if (skill) {
    skill->retain();
  }
  _currentSkill = skill;
}

int CharacterManager::getTension() {
  return _tension;
}

void CharacterManager::addTension(int t) {
  _tension += t;
  if (_tension > 4) _tension = 4;
}

void CharacterManager::resetTension() {
  _tension = 0;
}

void CharacterManager::addExp(int exp) {
  _exp += exp;
  _isExpDirty = true;
}

int CharacterManager::getLevel() {
  return this->getLevel(_exp);
}

int CharacterManager::getLevel(int exp) {
  if (_isExpDirty) {
    _levelCache = executeLuaFunction("getLevel", exp);
    _isExpDirty = false;
  }
  return _levelCache;
}

int CharacterManager::getExpWithLevel(int level) {
  return executeLuaFunction("getExp", level);
}

int CharacterManager::executeLuaFunction(const char *methodName, int argument) {
  CCLuaEngine* engine = CCLuaEngine::defaultEngine();
  std::string path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(FileUtils::getFilePath("Script/character/character.lua").c_str());
  engine->executeScriptFile(path.c_str());
  lua_State* L = engine->getLuaState();
  lua_getglobal(L, methodName);
  if (lua_isfunction(L, lua_gettop(L))) {
    engine->pushInt(argument);
    if (lua_pcall(L, 1, 1, 0)) {
      std::cout << lua_gettop(L) << std::endl;
      return 1;
    }
  }
  return (int)lua_tonumber(L, lua_gettop(L));
}

void CharacterManager::changeCharacter() {
  _currentCharacter = (Character*)_characters->objectAtIndex((this->getCurrentCharacterIndex() + 1) % 2);
}

int CharacterManager::getCurrentCharacterIndex() {
  return _characters->indexOfObject(this->getCurrentCharacter());
}

bool CharacterManager::getShield() {
  return _shield;
}

void CharacterManager::setShield(bool s) {
  _shield = s;
}

DamageType CharacterManager::damage(int damage) {
  // 属性とか後で考える
  DamageType damageType = DamageTypeHit;
  if (_shield) { // 盾装備中
    damage = 0;
    damageType = DamageTypeShield;
    this->setShield(false); // 盾問答無用で外します
  } else {
    _hp -= damage;
    if (_hp <= 0) { // 死亡時
      _hp = 0;
      damageType = DamageTypeDeath;
    }
  }
  DamageInfo info;
  info.damage = damage;
  info.damageType = damageType;
  _damageInfoQueue->push(info);
  return damageType;
}

int CharacterManager::addHP(int hp) {
  _hp += hp;
  if (_hp > _maxHP) {
    _hp = _maxHP;
  } else if (_hp < 0) {
    _hp = 0;
  }
  return _hp;
}

int CharacterManager::getHP() {
  return _hp;
}

int CharacterManager::getMP() {
  return _mp;
}

Skill* CharacterManager::getCurrentSkill() {
  return _currentSkill;
}

int CharacterManager::getExp() {
  return _exp;
}

void CharacterManager::setLevel(int l) {
  _exp = this->getExpWithLevel(l);
  _levelCache = l;
  _isExpDirty = false;
  this->updateParameters();
}

int CharacterManager::addMP(int mp) {
  _mp += mp;
  if (_mp > _maxMP) {
    _mp = _maxMP;
  } else if (_mp < 0) {
    _mp = 0;
  }
  return _mp;
}

int CharacterManager::getMaxHP() {
  return this->executeLuaFunction("getMaxHP", this->getLevel());
}

int CharacterManager::getMaxMP() {
  return this->executeLuaFunction("getMaxMP", this->getLevel());
}

void CharacterManager::updateParameters() {
  int currentMaxHP = _maxHP;
  int currentMaxMP = _maxMP;
  _maxHP = this->getMaxHP();
  _maxMP = this->getMaxMP();
  _hp = min(_maxHP, _hp + _maxHP - currentMaxHP);
  _mp = min(_maxMP, _mp + _maxMP - currentMaxMP);
}

float CharacterManager::getLevelOffsetRate(int attackLevel, int defenseLevel) {
  CCLuaEngine* engine = CCLuaEngine::defaultEngine();
  lua_State* L = engine->getLuaState();
  std::string path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(FileUtils::getFilePath("Script/character/character.lua").c_str());
  engine->executeScriptFile(path.c_str());
  lua_getglobal(L, "getLevelOffsetRate");
  lua_pushinteger(L, attackLevel);
  lua_pushinteger(L, defenseLevel);
  if (lua_pcall(L, 2, 1, 0)) {
    cout << lua_tostring(L, lua_gettop(L)) << endl;
  }
  float offset = lua_tonumber(L, lua_gettop(L));
  if (offset < 0) {
    return 0;
  }
  return offset;
}

int CharacterManager::getDrumLevel() {
  return _drumLevel;
}

void CharacterManager::setDrumLevel(int l) {
  _drumLevel = l;
}

Skill* CharacterManager::getLastSkill() {
  return _lastSkill;
}

std::queue<DamageInfo>* CharacterManager::getDamageInfoQueue() {
  return _damageInfoQueue;
}

int CharacterManager::getWaitTurn() {
  return _waitTurn;
}

int CharacterManager::getRepeatCount() {
  return _repeatCount;
}

int CharacterManager::getRepeatCountRaw() {
  return _repeatCountRaw;
}

void CharacterManager::setWaitTurn(int waitTurn) {
  _waitTurn = waitTurn;
}

void CharacterManager::setRepeatCount(int repeatCount) {
  _repeatCount = repeatCount;
}

void CharacterManager::setRepeatCountRaw(int repeatCount) {
  _repeatCountRaw = repeatCount;
}

CCArray* CharacterManager::getCharacters() {
  return _characters;
}