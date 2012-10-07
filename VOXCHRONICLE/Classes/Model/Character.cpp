//
//  Character.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/28.
//
//

#include "Character.h"
#include "Skill.h"

Character::Character(const char* slug) {
  _lua = new LuaObject(slug, "Character");
  _skills = CCArray::create();
  _skills->retain();
  CCLuaValueDict* dict = _lua->getTable("skills");
  for (map<string, CCLuaValue>::iterator it = dict->begin(); it != dict->end(); ++it) {
    string str = it->first;
    Skill* skill = new Skill(str.c_str());
    CCLuaValue value = it->second;
    int level = value.intValue();
    _skills->addObject(skill);
    skill->setAcquirementLV(level);
  }
  _name = _lua->getString("name");
  _slug = slug;
}

Character::~Character() {
  _skills->release();
  cout << "destruct" << endl;
}

const char* Character::getName() {
  return _name;
}

using namespace std;
CCArray* Character::getSkills() {
  return _skills;
}

CCArray* Character::getSkills(int level) {
  CCArray* array = CCArray::create();
  CCObject* obj = NULL;
  CCARRAY_FOREACH(_skills, obj) {
    if (((Skill*)obj)->getAcquirementLV() < level) {
      array->addObject(obj);
    }
  }
  return array;
}

const char* Character::getSlug() {
  return _slug;
}