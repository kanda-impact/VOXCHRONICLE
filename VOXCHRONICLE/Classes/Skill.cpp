//
//  Skill.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/29.
//
//

#include "Skill.h"

Skill::Skill(CCDictionary* info) {
  // テスト用にハードコード
  _name = "攻撃";
  _slug = "attack";
  _attack = 1;
  _maxRepeat = 4;
  _turn = 0;
  _range = SkillRangeSingle;
  _type = SkillTypePhysical;
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

int Skill::getAttack() {
  return _attack;
}