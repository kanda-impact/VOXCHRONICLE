//
//  Map.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/30.
//
//

#include <sstream>
#include "Map.h"
#include "Level.h"
#include "LuaObject.h"
#include "Enemy.h"
#include "FileUtils.h"

using namespace std;

Map::Map(const char* mapName) {
  // ここでスクリプトを読ませる
  stringstream ss;
  ss << "Script/map/" << mapName;
  _identifier = mapName;
  _lua = new LuaObject(ss.str().c_str(), "Map");
  _lua->retain();
  _name = new string(_lua->getString("name"));
  _prefix = new string(_lua->getString("prefix"));
  _backgroundImageName = new string(_lua->getString("backgroundImage"));
  CCLuaValueArray* nexts = _lua->getArray("nextMaps");
  _initialLevel = _lua->getInt("initialLevel");
  _maxLevel = _lua->getInt("maxLevel");
  _introCount = _lua->getInt("introCount");
  _bossPrefix = new string(_lua->getString("bossPrefix"));
  _nextMaps = new vector<string>();
  _fixedEnemyTable = new list< pair<string, int> >();
  for (CCLuaValueArray::const_iterator it = nexts->begin(); it != nexts->end(); ++it) {
    _nextMaps->push_back(it->stringValue());
  }
  
  CCLuaValueDict* table = _lua->getTable("fixedEnemies");
  if (table) {
    for (CCLuaValueDictIterator it = table->begin(); it != table->end(); ++it) {
      if (it->second.getType() != CCLuaValueTypeDict) {
        assert("fixedEnemies must contain array only.");
      }
      CCLuaValueDict array = it->second.dictValue();
      string enemy = array["1"].stringValue();
      int exp = array["2"].floatValue();
      pair<string, int> table(enemy, exp);
      _fixedEnemyTable->push_back(table);
    }
  }
}

Map::~Map() {
  delete _name;
  delete _fixedEnemyTable;
  delete _bossPrefix;
  delete _prefix;
  _lua->release();
}

Level* Map::createLevel(int level) {
  Level* lv = new Level(level);
  // モンスターテーブルを設定
  lua_State* L = _lua->getLuaEngine()->getLuaState();
  lua_getglobal(L, "Map");
  int table = lua_gettop(L);
  lua_getfield(L, table, "getEnemyTable");
  lua_pushinteger(L, level);
  if (lua_pcall(L, 1, 1, 0)) {
    cout << lua_tostring(L, lua_gettop(L)) << endl;
  }
  list< pair<string, int> > enemyTable;
  CCLuaValueDict* dict = _lua->recursivelyLoadTable(lua_gettop(L));
  for (CCLuaValueDict::iterator it = dict->begin(); it != dict->end(); ++it) {
    string key = it->first;
    CCLuaValue value = it->second;
    enemyTable.push_back( pair<string, int>(key, (int)value.floatValue()) );
  }
  lv->setEnemyTable(enemyTable);

  // モンスター出現率を設定
  lua_getglobal(L, "Map");
  table = lua_gettop(L);
  lua_getfield(L, table, "getEnemyPopRate");
  lua_pushinteger(L, level);
  if (lua_pcall(L, 1, 1, 0)) {
    cout << lua_tostring(L, lua_gettop(L)) << endl;
  }
  float enemyPopRate = lua_tonumber(L, lua_gettop(L));
  lv->setEnemyPopRate(enemyPopRate);
  
  return lv;
}

Level* Map::createInitialLevel() {
  return this->createLevel(_initialLevel);
}

string Map::getPrefixedMusicName(const char *musicName) {
  stringstream ss;
  ss << "Music/" << _prefix->c_str() << "/" << _prefix->c_str() << "_" << musicName;
  return FileUtils::getFilePath(ss.str().c_str());
}

int Map::getMaxLevel() {
  return _maxLevel;
}

int Map::getInitialLevel() {
  return _initialLevel;
  
}

CCArray* Map::getNextMaps() {
  CCArray* maps = CCArray::create();
  for (vector<string>::iterator it = _nextMaps->begin(); it != _nextMaps->end(); ++it) {
    Map* newMap = new Map(it->c_str());
    maps->addObject(newMap);
  }
  return maps;
}

string* Map::getName() {
  return _name;
}

int Map::getIntroCount() {
  return _introCount;
}

CCArray* Map::getFixedEnemies(int preExp, int currentExp) {
  CCArray* enemies = CCArray::create();
  list< pair<string, int> > poped;
  for (list< pair<string, int> >::iterator it = _fixedEnemyTable->begin(); it != _fixedEnemyTable->end(); ++it) {
    int exp = it->second;
    if (exp <= currentExp ) {
      Enemy* enemy = Enemy::create(it->first.c_str());
      enemies->addObject(enemy);
      poped.push_back(*it);
    }
  }
  for (list< pair<string, int> >::iterator it = poped.begin(); it != poped.end(); ++it) {
    _fixedEnemyTable->remove(*it);
  }
  return enemies;
}

bool Map::isBossStage() {
  return _bossPrefix->length() > 0;
}