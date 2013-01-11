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
#include "TrackCache.h"

MusicSet::MusicSet(const char* identifier) {
  stringstream ss;
  ss << "Script/musics/" << identifier << ".lua";
  _lua = new LuaObject(FileUtils::getFilePath(ss.str().c_str()).c_str());
  _lua->retain();
  _introCount = _lua->getInt("introCount");
  _finishCount = _lua->getInt("finishCount");
  _type = (MusicSetType)_lua->getInt("type");
  _name = new string(_lua->getString("name"));
  _composer = new string(_lua->getString("composer"));
  _prefix = new string(_lua->getString("prefix"));
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
  delete _name;
  delete _composer;
  delete _prefix;
  delete _common;
  delete _ignoreDrums;
  _lua->release();
}

string MusicSet::getPrefixedMusicName(const char *musicName) {
  stringstream ss;
  ss << "Music/" << _prefix->c_str() << "/" << _prefix->c_str() << "_" << musicName;
  return FileUtils::getFilePath(ss.str().c_str());
}

bool MusicSet::isCommon(const char *skillName) {
  // 未実装。今は恒久的にtrueを返し続けます
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
  string musics[] ={
    string("counter0.caf"),
    string("counter1.caf"),
    string("counter2.caf"),
    string("drum0.caf"),
    string("drum1.caf"),
    string("drum2.caf"),
    string("drum3.caf"),
    string("finish0.caf"),
    string("finish1.caf"),
    string("finish2.caf"),
    string("finish3.caf"),
    string("impact0.caf"),
    string("impact1.caf"),
    string("impact2.caf"),
    string("intro0.caf"),
    string("intro1.caf"),
    string("lskbow0.caf"),
    string("lskchange0.caf"),
    string("lskcure0.caf"),
    string("lskmagic0.caf"),
    string("lskmagic1.caf"),
    string("lskmagic2.caf"),
    string("lskmagic3.caf"),
    string("lskthunder0.caf"),
    string("miss.caf"),
    string("run0.caf"),
    string("run1.caf"),
    string("shield0.caf"),
    string("silent.caf"),
    string("tension0.caf"),
    string("tension1.caf"),
    string("tension2.caf"),
    string("tension3.caf"),
    string("voxattack0.caf"),
    string("voxattack1.caf"),
    string("voxattack2.caf"),
    string("voxattack3.caf"),
    string("voxchange0.caf"),
    string("voxcharge0.caf"),
    string("voxknockback0.caf"),
    string("voxslash0.caf"),
    string("wait0.caf")
  };
  for (int i = 0; i < 41; ++i) {
    string path = this->getPrefixedMusicName(musics[i].c_str());
    TrackCache::sharedCache()->addTrack(path.c_str(), 0);
    TrackCache::sharedCache()->addTrack(path.c_str(), 1);
  }
}