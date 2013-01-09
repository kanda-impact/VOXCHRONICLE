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
    string("counter0.mp3"),
    string("counter1.mp3"),
    string("counter2.mp3"),
    string("drum0.mp3"),
    string("drum1.mp3"),
    string("drum2.mp3"),
    string("drum3.mp3"),
    string("finish0.mp3"),
    string("finish1.mp3"),
    string("finish2.mp3"),
    string("finish3.mp3"),
    string("impact0.mp3"),
    string("impact1.mp3"),
    string("impact2.mp3"),
    string("intro0.mp3"),
    string("intro1.mp3"),
    string("lskbow0.mp3"),
    string("lskchange0.mp3"),
    string("lskcure0.mp3"),
    string("lskmagic0.mp3"),
    string("lskmagic1.mp3"),
    string("lskmagic2.mp3"),
    string("lskmagic3.mp3"),
    string("lskthunder0.mp3"),
    string("miss.mp3"),
    string("run0.mp3"),
    string("run1.mp3"),
    string("shield0.mp3"),
    string("silent.mp3"),
    string("tension0.mp3"),
    string("tension1.mp3"),
    string("tension2.mp3"),
    string("tension3.mp3"),
    string("voxattack0.mp3"),
    string("voxattack1.mp3"),
    string("voxattack2.mp3"),
    string("voxattack3.mp3"),
    string("voxchange0.mp3"),
    string("voxcharge0.mp3"),
    string("voxknockback0.mp3"),
    string("voxslash0.mp3"),
    string("wait.mp3")
  };
  for (int i = 0; i < 41; ++i) {
    string path = this->getPrefixedMusicName(musics[i].c_str());
    TrackCache::sharedCache()->addTrack(path.c_str(), 0);
    TrackCache::sharedCache()->addTrack(path.c_str(), 1);
  }
}