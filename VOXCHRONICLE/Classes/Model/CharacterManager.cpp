//
//  CharacterManager.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/28.
//
//

#include <sstream>
#include "CharacterManager.h"
#include "Skill.h"
#include "CCLuaEngine.h"

CharacterManager::CharacterManager() {
  Character* vox = new Character("vox");
  vox->autorelease();
  
  Character* lsk = new Character("lsk");
  lsk->autorelease();
  
  _characters = CCArray::create(vox, lsk, NULL);
  _characters->retain();
  _currentCharacter = vox;
  _repeatCount = 0;
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
}

CharacterManager::~CharacterManager() {
  _characters->release();
  if (_lastSkill) _lastSkill->release();
  if (_currentSkill) _currentSkill->release();
}

Character* CharacterManager::getCurrentCharacter() {
  return _currentCharacter;
}

const char* CharacterManager::checkSkillTrackName(Skill* skill, SkillPerformType& performeType) {
  performeType = SkillPerformTypeNone;
  if (skill) {
    _waitTurn += 1;
    if (_waitTurn == skill->getTurn()) {
      std::stringstream ss;
      if (_lastSkill && strcmp(_lastSkill->getSlug(), skill->getSlug())) {
        _repeatCount = 0;
      }
      if (skill->isCommon()) {
        // スキルのcommonがfalseのとき、曲名にキャラ名が付かない
        // tension0.wav
        ss << skill->getSlug() << _repeatCount;
      } else {
        // commonがtrueのとき、曲名にキャラ名が付く
        // ex: voxattack0.wav
        ss << _currentCharacter->getSlug() << skill->getSlug() << _repeatCount;
      }
      _repeatCount = (_repeatCount + 1) % skill->getMaxRepeat();
      this->setLastSkill(skill);
      this->setCurrentSkill(NULL);
      _waitTurn = 0;
      if (skill->getMP() <= this->getMP()) {
        // MP足りてるときだけ
        performeType = SkillPerformTypeSuccess;
        return ss.str().c_str();
      } else {
        performeType = SkillPerformTypeFailure;
        return "miss"; // MP足りてないとき、ミス音を返す
      }
    } else {
      this->setCurrentSkill(skill);
      performeType = SkillPerformTypeCharge;
      std::stringstream ss;
      ss << _currentCharacter->getSlug() << skill->getSlug() << "_charge" << (_waitTurn - 1); // チャージ中の時、チャージ音返す
      return ss.str().c_str();
    }
  } else {
    _repeatCount = 0;
    this->setLastSkill(skill);
  }
  return "silent";
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
  if (_tension >= 4) _tension = 3;
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
  std::string path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("character.lua");
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
  if (_shield) {
    return DamageTypeShield;
  }
  _hp -= damage;
  if (_hp <= 0) {
    return DamageTypeDeath;
  }
  return DamageTypeHit;
}

int CharacterManager::cureHP(int hp) {
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
}

void CharacterManager::useMP(int mp) {
  _mp -= mp;
  if (_mp > _maxMP) {
    _mp = _maxMP;
  } else if (_mp < 0) {
    _mp = 0;
  }
}

int CharacterManager::getMaxHP() {
  return this->executeLuaFunction("getMaxHP", this->getLevel());
}

int CharacterManager::getMaxMP() {
  return this->executeLuaFunction("getMaxMP", this->getLevel());
}

void CharacterManager::updateParameters() {
  float rateHP = (float)_hp / (float)_maxHP;
  float rateMP = (float)_mp / (float)_maxMP;
  _maxHP = this->getMaxHP();
  _maxMP = this->getMaxMP();
  _hp = _maxHP * rateHP;
  _mp = _maxMP * rateMP;
}