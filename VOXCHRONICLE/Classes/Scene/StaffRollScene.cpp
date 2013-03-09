//
//  StaffRollScene.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/3/3.
//
//

#include "StaffRollScene.h"
#include "Map.h"
#include <boost/bind.hpp>
#include <sstream>

#define EXT ".caf"

using namespace std;
using namespace boost;

const char* kLuaFileName = "staffroll";

StaffRollScene::StaffRollScene(CCArray* maps) {
  _music = new Music(3);
  _music->setTrackDidBackFunction(boost::bind(&StaffRollScene::trackDidBack, this, _1, _2, _3));
  _music->setTrackDidFinishFunction(boost::bind(&StaffRollScene::trackDidFinishPlaying, this, _1, _2, _3, _4));
  _music->setTrackWillFinishFunction(boost::bind(&StaffRollScene::trackWillFinishPlaying, this, _1, _2, _3, _4));
  _currentCharacterType = CharacterTypeVox;
  
  _lua = LuaObject::create(kLuaFileName);
  _lua->retain();
  CCObject* obj = NULL;
  CCARRAY_FOREACH(maps, obj) {
    Map* map = (Map*)obj;
    this->pushTracksFor(map->getWayMusic());
  }
}

StaffRollScene::~StaffRollScene() {
  _music->release();
  _lua->release();
}

void StaffRollScene::onEnterTransitionDidFinish() {
  _music->play();
}

void StaffRollScene::trackDidBack(VISS::Music *music, VISS::Track *currentTrack, int trackNumber) {
}

void StaffRollScene::trackWillFinishPlaying(VISS::Music *music, VISS::Track *currentTrack, VISS::Track *nextTrack, int trackNumber) {
}

void StaffRollScene::trackDidFinishPlaying(VISS::Music *music, VISS::Track *finishedTrack, VISS::Track *nextTrack, int trackNumber) {
  
}

void StaffRollScene::pushTracksFor(MusicSet* set) {
  lua_State* L = _lua->getLuaEngineWithLoad()->getLuaState();
  CCLuaValueArray* tracks = _lua->getArray("tracks");
  for (CCLuaValueArrayIterator it = tracks->begin(); it != tracks->end(); ++it) {
    string track = it->stringValue();
    if (track == "intro") {
      this->pushTracks("intro", set->getIntroCount(), set);
    } else if (track == "finish") {
      this->pushTracks("finish", set->getFinishCount(), set);
    } else if (track == "change") {
      if (_currentCharacterType == CharacterTypeVox) {
        _currentCharacterType = CharacterTypeLaska;
        this->pushTrack("voxchange0", set);
      } else {
        _currentCharacterType = CharacterTypeVox;
        this->pushTrack("lskchange0", set);
      }
    } else if (track == "wait") {
      if (_currentCharacterType == CharacterTypeVox) {
        this->pushWaitTracks("vox", set);
      } else {
        this->pushWaitTracks("lsk", set);
      }
    } else {
      cout << track << endl;
      this->pushTrack(track.c_str(), set);
    }
  }
}

void StaffRollScene::pushTrack(const char *identifier, MusicSet* set) {
  stringstream ss;
  ss << identifier << EXT;
  _music->pushTrack(set->getPrefixedMusicName(ss.str().c_str()).c_str(), MusicChannelMain);
  // ドラムとリフは仮ですが、いずれランダムで載るようにする？
  _music->pushTrack(set->getPrefixedMusicName((string("silent") + string(EXT)).c_str()).c_str(), MusicChannelCounter);
  _music->pushTrack(set->getPrefixedMusicName((string("silent") + string(EXT)).c_str()).c_str(), MusicChannelDrum);
}

void StaffRollScene::pushTracks(const char *identifier, int count, MusicSet* set) {
  for (int i = 0; i < count; ++i) {
    stringstream ss;
    ss << identifier << i << EXT;
    _music->pushTrack(set->getPrefixedMusicName(ss.str().c_str()).c_str(), MusicChannelMain);
    _music->pushTrack(set->getPrefixedMusicName((string("silent") + string(EXT)).c_str()).c_str(), MusicChannelCounter);
    _music->pushTrack(set->getPrefixedMusicName((string("silent") + string(EXT)).c_str()).c_str(), MusicChannelDrum);
  }
}

void StaffRollScene::pushWaitTracks(const char *characterIdentifier, MusicSet* set) {
  int waitCount = set->getWaitCount();
  for (int i = 0; i < waitCount; ++i) {
    stringstream ss;
    if (!set->isCommon("wait")) {
      ss << characterIdentifier;
    }
    ss << "wait" << i << EXT;
    _music->pushTrack(set->getPrefixedMusicName(ss.str().c_str()).c_str(), MusicChannelMain);
    _music->pushTrack(set->getPrefixedMusicName((string("silent") + string(EXT)).c_str()).c_str(), MusicChannelCounter);
    _music->pushTrack(set->getPrefixedMusicName((string("silent") + string(EXT)).c_str()).c_str(), MusicChannelDrum);
  }
}