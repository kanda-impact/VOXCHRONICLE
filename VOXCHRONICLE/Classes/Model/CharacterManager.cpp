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
  CCArray* skills = CCArray::create(new Skill("attack"),
                                    new Skill("knockback"),
                                    new Skill("tension"),
                                    new Skill("change"),
                                    new Skill("shield"),
                                    NULL);
  Character* vox = new Character(skills);
  vox->autorelease();
  vox->setName("オクス");
  vox->setSlug("vox");
  
  CCArray* lskSkills = CCArray::create(new Skill("magic"),
                                       new Skill("thunder"),
                                       new Skill("tension"),
                                       new Skill("change"),
                                       new Skill("shield"),
                                       NULL);
  Character* lsk = new Character(lskSkills);
  lsk->setName("ラスカ");
  lsk->setSlug("lsk");
  
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
  _hp = 5;
  _maxHP = _hp;
  _mp = 0;
}

CharacterManager::~CharacterManager() {
  _characters->release();
  if (_lastSkill) _lastSkill->release();
  if (_currentSkill) _currentSkill->release();
}

Character* CharacterManager::getCurrentCharacter() {
  return _currentCharacter;
}

const char* CharacterManager::performSkill(Skill* skill) {
  if (skill) {
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
    return ss.str().c_str();
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

void CharacterManager::chargeTension() {
  if (_tension < 4) _tension += 1;
}

void CharacterManager::resetTension() {
  _tension = 0;
}

int CharacterManager::calcDamage(Enemy *enemy, Skill *skill) {
  const float tensions[] = {1.0, 1.5, 3.0, 4.5, 6};
  // ToDo 属性によるダメージ軽減とかもこの辺に載せてやる
  int result = round(skill->getPower() * tensions[_tension]);
  return result;
}

void CharacterManager::addExp(int exp) {
  _exp += exp;
}

int CharacterManager::getLevel(int exp) {
  CCLuaEngine* engine = CCLuaEngine::defaultEngine();
  std::string path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("exp.lua");
  engine->executeScriptFile(path.c_str());
  lua_State* L = engine->getLuaState();
  lua_getglobal(L, "getLevel");
  if (lua_isfunction(L, lua_gettop(L))) {
    engine->pushInt(exp);
    if (lua_pcall(L, 1, 1, 0)) {
      std::cout << lua_gettop(L) << std::endl;
      return 1;
    }
  }
  return lua_tointeger(L, lua_gettop(L));
}

void CharacterManager::setCurrentCharacter(int idx) {
  _currentCharacter = (Character*)_characters->objectAtIndex(idx);
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

DamageType CharacterManager::damage(Enemy *attacker, int damage) {
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

int CharacterManager::getHP() {
  return _hp;
}

int CharacterManager::getMP() {
  return _mp;
}
