//
//  Species.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/2/15.
//
//

#include "Species.h"
#include "LuaObject.h"

Species::Species(const char* identifier) {
  _identifier = identifier;
  _lua = new LuaObject(identifier);
  _baseExp = _lua->getInt("baseExp");
  _name = string(_lua->getString("name"));
  _attack = _lua->getInt("attack");
  _counter = _lua->getInt("counter");
  _imageName = string(_lua->getString("imageName")) + ".png";
  _animationFrames = _lua->getInt("animationFrames");
  _hasFrame = _lua->getBoolean("hasFrame");
  _disableSkills = _lua->getArray("disableSkills");
}

Species::~Species() {
  _lua->release();
  delete _disableSkills;
}

string Species::getIdentifier() {
  return _identifier;
}

string Species::getImageName() {
  return _imageName;
}

string Species::getName() {
  return _name;
}

int Species::getAttack() {
  return _attack;
}

int Species::getCounter() {
  return _counter;
}

int Species::getAnimationFrames() {
  return _animationFrames;
}

bool Species::hasFrame() {
  return _hasFrame;
}

string Species::choiceEnemySkill(CCObject* enemy, CCObject* characterManager, CCObject* enemyManager) {
  lua_State* L = _lua->getLuaEngineWithLoad()->getLuaState();
  lua_getglobal(L, "Enemy");
  lua_getfield(L, lua_gettop(L), "performSkill");
  if (lua_isfunction(L, lua_gettop(L))) {
    _lua->pushCCObject(enemy, "Enemy");
    _lua->pushCCObject(characterManager, "CharacterManager");
    _lua->pushCCObject(enemyManager, "EnemyManager");
    if (lua_pcall(L, 3, 1, 0)) {
      cout << lua_tostring(L, lua_gettop(L)) << endl;
      return "";
    }
    string skillName = lua_tostring(L, lua_gettop(L));
    return skillName;
  }
  return "";
}

int Species::getDefaultExp(int level, int maxHP, EnemyItem item, SkillType type) {
  LuaObject* obj = LuaObject::create("character");
  lua_State* L = obj->getLuaEngineWithLoad()->getLuaState();
  lua_getglobal(L, "getDefaultExp");
  if (lua_isfunction(L, lua_gettop(L))) {
    lua_pushinteger(L, _baseExp);
    lua_pushinteger(L, level);
    lua_pushinteger(L, maxHP);
    lua_pushinteger(L, item);
    lua_pushinteger(L, type);
    if (lua_pcall(L, 5, 1, 0)) {
      cout << lua_tostring(L, lua_gettop(L)) << endl;
    }
    float exp = lua_tonumber(L, lua_gettop(L));
    return ceil(exp);
  }
  return 0;
}

LuaObject* Species::getLuaObject() {
  return _lua;
}

bool Species::isEnableSkill(Skill *skill) {
  for (CCLuaValueArrayIterator it = _disableSkills->begin(); it != _disableSkills->end(); ++it) {
    if (skill->getIdentifier() == it->stringValue()) {
      return false;
    }
  }
  return true;
}

string Species::getDescription() {
  return _lua->getString("description");
}

string Species::getHabitat() {
  return _lua->getString("habitat");
}