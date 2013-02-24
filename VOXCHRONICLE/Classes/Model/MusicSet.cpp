//
//  MusicSet.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/12/31.
//
//

#include "MusicSet.h"
#include "FileUtils.h"
#include <sstream>

MusicSet::MusicSet(const char* identifier) {
  stringstream ss;
  ss << "Script/musics/" << identifier << ".lua";
  _lua = new LuaObject(FileUtils::getFilePath(ss.str().c_str()).c_str());
  _introCount = _lua->getInt("introCount");
  _finishCount = _lua->getInt("finishCount");
  _type = (MusicSetType)_lua->getInt("type");
  _name = string(_lua->getString("name"));
  _composer = string(_lua->getString("composer"));
  _prefix = string(_lua->getString("prefix"));
  _waitCount = _lua->getInt("waitCount");
  // ToDo 今は使わないのであとで載せます _common, _ignoreDrums;
  lua_State* L = _lua->getLuaEngine()->getLuaState();
  lua_getglobal(L, "Music");
  lua_getfield(L, lua_gettop(L), "common");
  _common = _lua->recursivelyLoadTable(lua_gettop(L));
  lua_getglobal(L, "Music");
  lua_getfield(L, lua_gettop(L), "ignoreDrums");
  _ignoreDrums = _lua->recursivelyLoadTable(lua_gettop(L));
}

MusicSet::~MusicSet() {
  delete _common;
  delete _ignoreDrums;
  _lua->release();
}

string MusicSet::getPrefixedMusicName(const char *musicName) {
  stringstream ss;
  ss << "Music/" << _prefix.c_str() << "/" << _prefix.c_str() << "_" << musicName;
  return FileUtils::getFilePath(ss.str().c_str());
}

bool MusicSet::isCommon(const char *skillName) {
  if (_common->count(string(skillName)) == 1) {
    return _common->at(skillName).booleanValue();
  }
  return true;
}

int MusicSet::getIntroCount() {
  return _introCount;
}

int MusicSet::getFinishCount() {
  return _finishCount;
}

int MusicSet::getWaitCount() {
  return _waitCount;
}

MusicSetType MusicSet::getType() {
  return _type;
}

void MusicSet::preloadAllTracks() {
  // とりあえずテスト用にハードコードします
}

string MusicSet::getName() {
  return _name;
}

string MusicSet::getComposer() {
  return _composer;
}