//
//  Skill.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/29.
//
//

#include <sstream>
#include <string>
#include "Skill.h"
#include "LuaObject.h"

Skill::Skill(const char* slug) {
  stringstream ss;
  ss << "Script/skills/" << slug;
  _lua = new LuaObject(ss.str().c_str(), "Skill");
  _lua->retain();
  _name = new std::string(_lua->getString("name"));
  _slug = _lua->getString("slug");
  _power = _lua->getInt("power");
  _mp = _lua->getInt("mp");
  _common = _lua->getBoolean("common");
  _maxRepeat = _lua->getInt("maxRepeat");
  _turn = _lua->getInt("turn");
  _tensionLevel = _lua->getInt("tensionLevel");
  _range = (SkillRange)_lua->getInt("skillRange");
  _type = (SkillType)_lua->getInt("skillType");
}

Skill::~Skill() {
  delete _name;
  _lua->release();
}

const char* Skill::getName() {
  return _name->c_str();
}

const char* Skill::getSlug() {
  return _slug;
}

int Skill::getTurn() {
  return _turn;
}

int Skill::getMaxRepeat() {
  return _maxRepeat;
}

int Skill::getPowerWithTension(int tension) {
  lua_State* L = _lua->getLuaEngine()->getLuaState();
  lua_getglobal(L, "Skill");
  int table = lua_gettop(L);
  lua_getfield(L, table, "getTensionRate");
  float rate;
  if (lua_isfunction(L, -1)) {
    // skill.luaにgetTensionRateが実装済みのとき
    lua_pushinteger(L, tension);
    if (lua_pcall(L, 1, 1, 0)) {
      cout << lua_tostring(L, lua_gettop(L)) << endl;
    }
    rate = lua_tonumber(L, -1);
  } else {
    // されていないとき。デフォルトのテンション上昇値を使う
    const float tensions[] = {1.0, 1.5, 3.0, 4.5, 6};
    rate = tensions[tension];
  }
  return _power * rate;
}

int Skill::getMP() {
  return _mp;
}

bool Skill::isCommon() {
  return _common;
}

SkillRange Skill::getRange() {
  return _range;
}

SkillType Skill::getType() {
  return _type;
}

LuaObject* Skill::getLuaObject() {
  return _lua;
}

int Skill::getAcquirementLV() {
  return _acquirementLV;
}

void Skill::setAcquirementLV(int lv) {
  _acquirementLV = lv;
}

int Skill::getTensionLevel() {
  return _tensionLevel;
}