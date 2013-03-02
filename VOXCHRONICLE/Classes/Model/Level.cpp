//
//  Level.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/29.
//
//

#include "Level.h"
#include <boost/lexical_cast.hpp>
#include "Map.h"

Level::Level(int level, Map* map) {
  _level = level;
  _skillTable = CCDictionary::create();
  _skillTable->retain();
  _map = map; // weakなので、retainしない。参照だけ持っておく
}

Level::~Level() {
  _skillTable->release();
}

int Level::getLevel() {
  return _level;
}

list< pair<string, int> > Level::getEnemyTable() {
  return _enemyTable;
}

void Level::setEnemyTable(list<pair<string, int> > table) {
  _enemyTable = table;
}

float Level::getEnemyPopRate() {
  return _enemyPopRate;
}

void Level::setEnemyPopRate(float rate) {
  _enemyPopRate = rate;
}

CCArray* Level::getSkills(Character *character) {
  CCArray* array = CCArray::create();
  CCArray* all = this->getAllSkills(character);
  CCObject* obj = NULL;
  CCARRAY_FOREACH(all, obj) {
    if (((Skill*)obj)->getAcquirementLV() <= _level) {
      array->addObject(obj);
    }
  }
  return array;
}

CCArray* Level::getAllSkills(Character* character) {
  return (CCArray*)_skillTable->objectForKey(character->getIdentifier().c_str());
}

void Level::setSkillTable(CCDictionary* skillTable) {
  if (_skillTable) {
    _skillTable->release();
  }
  _skillTable = skillTable;
  if (skillTable) {
    skillTable->retain();
  }
}
