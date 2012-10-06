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
  std::stringstream ss;
  ss << slug << ".lua";
  LuaObject* lua = new LuaObject(ss.str().c_str(), "params");
  lua->autorelease();
  _name = new std::string(lua->getString("name"));
  _slug = slug;
  _power = lua->getInt("power");
  _mp = lua->getInt("mp");
  _common = lua->getBoolean("common");
  _maxRepeat = lua->getInt("maxRepeat");
  _turn = lua->getInt("turn");
  _range = (SkillRange)lua->getInt("skillRange");
  _type = (SkillType)lua->getInt("skillType");
}

Skill::~Skill() {
  delete _name;
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

int Skill::getPower() {
  return _power;
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