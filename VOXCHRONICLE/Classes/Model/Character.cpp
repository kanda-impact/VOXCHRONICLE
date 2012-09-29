//
//  Character.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/28.
//
//

#include "Character.h"

Character::Character(CCArray* skills) {
  _skills = skills;
  _skills->retain();
  _name = "オクス"; // とりあえずハードコード
  _slug = "vox";
}

Character::~Character() {
  _skills->release();
}

const char* Character::getName() {
  return _name;
}

CCArray* Character::getSkills() {
  return _skills;
}

const char* Character::getSlug() {
  return _slug;
}