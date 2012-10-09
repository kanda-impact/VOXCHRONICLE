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

using namespace std;

Map::Map(const char* mapName) {
  // ここでスクリプトを読ませる
  _slug = mapName;
  _lua = new LuaObject(mapName, "Map");
  _lua->retain();
  _name = new string(_lua->getString("name"));
  _prefix = new string(_lua->getString("prefix"));
  _backgroundImageName = new string(_lua->getString("backgroundImage"));
  CCLuaValueArray* nexts = _lua->getArray("nextMaps");
  _initialLevel = _lua->getInt("initialLevel");
  _maxLevel = _lua->getInt("maxLevel");
  _nextMaps = new vector<string>();
  for (CCLuaValueArray::const_iterator it = nexts->begin(); it != nexts->end(); ++it) {
    _nextMaps->push_back(it->stringValue());
  }
}

Map::~Map() {
  delete _name;
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

const char* Map::getPrefixedMusicName(const char *musicName) {
  stringstream ss;
  ss << _prefix->c_str() << "_" << musicName;
  return ss.str().c_str();
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