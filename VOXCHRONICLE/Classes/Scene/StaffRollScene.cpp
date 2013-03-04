//
//  StaffRollScene.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/3/3.
//
//

#include "StaffRollScene.h"
#include <boost/bind.hpp>

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
    this->pushTracksFor(map);
  }
}

StaffRollScene::~StaffRollScene() {
  _music->release();
  _lua->release();
}

void StaffRollScene::onEnterTransitionDidFinish() {
}

void StaffRollScene::trackDidBack(VISS::Music *music, VISS::Track *currentTrack, int trackNumber) {
}

void StaffRollScene::trackWillFinishPlaying(VISS::Music *music, VISS::Track *currentTrack, VISS::Track *nextTrack, int trackNumber) {
}

void StaffRollScene::trackDidFinishPlaying(VISS::Music *music, VISS::Track *finishedTrack, VISS::Track *nextTrack, int trackNumber) {
  
}

void StaffRollScene::pushTracksFor(Map *map) {
  lua_State* L = _lua->getLuaEngineWithLoad()->getLuaState();
  CCLuaValueArray* tracks = _lua->getArray("tracks");
  for (CCLuaValueArrayIterator it = tracks->begin(); it != tracks->end(); ++it) {
    string track = it->stringValue();
  }
}