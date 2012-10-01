//
//  Map.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/30.
//
//

#include <sstream>
#include "Map.h"
#include "LuaObject.h"

using namespace std;

Map::Map(const char* mapName) {
  // ここでスクリプトを読ませる
  _slug = mapName;
  stringstream ss;
  ss << mapName << ".lua";
  LuaObject* lua = new LuaObject(ss.str().c_str(), "Map");
  _name = new string(lua->getString("name"));
  _prefix = new string(lua->getString("prefix"));
  _backgroundImageName = new string(lua->getString("backgroundImage"));
  CCLuaValueDict* nexts = lua->getTable("nextMaps");
  _initialLevel = lua->getInt("initialLevel");
  for (int i = 1; i <= nexts->size(); ++i) {
    stringstream ss;
    ss << i;
    _nextMaps->push_back((*nexts)[ss.str()].stringValue());
  }
  delete lua;
}

Map::~Map() {
  delete _name;
}

Level* Map::createLevel(int level) {
  return NULL;
}

const char* Map::getPrefixedMusicName(const char *musicName) {
  stringstream ss;
  ss << _prefix->c_str() << "_" << musicName;
  return ss.str().c_str();
}