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
  CCLuaValueDict* sks = _lua->getTable("skills");
  cout << sks->size() << endl;
  for (int i = 1; i <= sks->size(); ++i) {
    stringstream ss;
    ss << i;
    CCLuaValueDict a = (*sks)[ss.str()].dictValue();
    string skillName;
    int alv = 0;
    for (int i = 1; i <= 2; ++i) {
      if (i == 1) {
        skillName = a["1"].stringValue();
      } else if (i == 2){
        alv = a["2"].floatValue();
      }
    }
    Skill* skill = new Skill(skillName.c_str());
    skill->setAcquirementLV(alv);
    _skills->addObject(skill);
  }
  _name = _lua->getString("name");
  _slug = slug;
}

Character::~Character() {
  _skills->release();
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