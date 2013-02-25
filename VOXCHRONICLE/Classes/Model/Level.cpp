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
  _skillDictionary = CCDictionary::create();
  _skillDictionary->retain();
  _map = map; // weakなので、retainしない。参照だけ持っておく
}

Level::~Level() {
  _skillDictionary->release();
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
  return (CCArray*)_skillDictionary->objectForKey(character->getIdentifier().c_str());
}

void Level::loadSkills(Character* character) {
  CCArray* skills = CCArray::create();
  skills->retain();
  LuaObject* lua = LuaObject::create(character->getIdentifier().c_str());
  lua_State* L = lua->getLuaEngineWithLoad()->getLuaState();
  lua_getfield(L, lua_gettop(L), "getSkills");
  if (lua_isfunction(L, lua_gettop(L))) {
    lua_pushstring(L, _map->getIdentifier().c_str()); // Map名をpushしてやる
    if (lua_pcall(L, 1, 1, 0)) {
      cout << lua_tostring(L, lua_gettop(L)) << endl;
    }
    CCLuaValueDict* sks = lua->recursivelyLoadTable(lua_gettop(L));
    for (int i = 1; i <= sks->size(); ++i) {
      CCLuaValueDict a = (*sks)[boost::lexical_cast<string>(i).c_str()].dictValue();
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
      skills->addObject(skill);
    }
    _skillDictionary->setObject(skills, character->getIdentifier());
  }
  
}