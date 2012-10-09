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
  _lua = new LuaObject(slug, "Skill");
  _lua->retain();
  _name = new std::string(_lua->getString("name"));
  _slug = _lua->getString("slug");
  _power = _lua->getInt("power");
  _mp = _lua->getInt("mp");
  _common = _lua->getBoolean("common");
  _maxRepeat = _lua->getInt("maxRepeat");
  _turn = _lua->getInt("turn");
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

LuaObject* Skill::getLuaObject() {
  return _lua;
}

int Skill::getAcquirementLV() {
  return _acquirementLV;
}

void Skill::setAcquirementLV(int lv) {
  _acquirementLV = lv;
}