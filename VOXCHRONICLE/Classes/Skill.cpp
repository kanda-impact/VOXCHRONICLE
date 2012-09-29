//
//  Skill.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/29.
//
//

#include <sstream>
#include "Skill.h"
#include "LuaCocos2d.h"
#include "LuaObject.h"

Skill::Skill(const char* slug) {
  std::ostringstream os;
  os << slug << ".lua";
  LuaObject* lua = new LuaObject(os.str().c_str(), "params");
  
  std::cout << lua << std::endl;
  _name = lua->getString("name");
  _slug = slug;
  _power = lua->getInt("power");
  _maxRepeat = lua->getInt("maxRepeat");
  _turn = lua->getInt("turn");
  _range = (SkillRange)lua->getInt("skillRange");
  _type = (SkillType)lua->getInt("skillType");
}

Skill::~Skill() {
}

const char* Skill::getName() {
  return _name;
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

SkillRange Skill::getRange() {
  return _range;
}

SkillType Skill::getType() {
  return _type;
}