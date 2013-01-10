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
    string("counter0.m4a"),
    string("counter1.m4a"),
    string("counter2.m4a"),
    string("drum0.m4a"),
    string("drum1.m4a"),
    string("drum2.m4a"),
    string("drum3.m4a"),
    string("finish0.m4a"),
    string("finish1.m4a"),
    string("finish2.m4a"),
    string("finish3.m4a"),
    string("impact0.m4a"),
    string("impact1.m4a"),
    string("impact2.m4a"),
    string("intro0.m4a"),
    string("intro1.m4a"),
    string("lskbow0.m4a"),
    string("lskchange0.m4a"),
    string("lskcure0.m4a"),
    string("lskmagic0.m4a"),
    string("lskmagic1.m4a"),
    string("lskmagic2.m4a"),
    string("lskmagic3.m4a"),
    string("lskthunder0.m4a"),
    string("miss.m4a"),
    string("run0.m4a"),
    string("run1.m4a"),
    string("shield0.m4a"),
    string("silent.m4a"),
    string("tension0.m4a"),
    string("tension1.m4a"),
    string("tension2.m4a"),
    string("tension3.m4a"),
    string("voxattack0.m4a"),
    string("voxattack1.m4a"),
    string("voxattack2.m4a"),
    string("voxattack3.m4a"),
    string("voxchange0.m4a"),
    string("voxcharge0.m4a"),
    string("voxknockback0.m4a"),
    string("voxslash0.m4a"),
    string("wait0.m4a")
  };
  for (int i = 0; i < 41; ++i) {
    string path = this->getPrefixedMusicName(musics[i].c_str());
    TrackCache::sharedCache()->addTrack(path.c_str(), 0);
    TrackCache::sharedCache()->addTrack(path.c_str(), 1);
  }
}