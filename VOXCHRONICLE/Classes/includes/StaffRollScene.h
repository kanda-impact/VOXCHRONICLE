//
//  StaffRollScene.h
//  VOXCHRONICLE
//
//  Created by giginet on 2013/3/3.
//
//

#ifndef __VOXCHRONICLE__StaffRollScene__
#define __VOXCHRONICLE__StaffRollScene__

#include <iostream>
#include "cocos2d.h"
#include "Music.h"
#include "Track.h"
#include "LuaObject.h"

#include "MusicManager.h"
#include "CharacterManager.h"
#include "EnemyManager.h"

using namespace VISS;
using namespace cocos2d;

typedef enum {
  TextTypeSection,
  TextTypeText,
  TextTypeDescription
} TextType;

class StaffRollScene :public CCLayer {
 private:
  int _maxTrackCount;
  int _trackCount;
  int _textIndex;
  deque<bool>* _isAddCutin;
  CCArray* _texts;
  Music* _music;
  LuaObject* _lua;
  CharacterType _currentCharacterType;
  void trackDidBack(Music* music, Track* currentTrack, int trackNumber);
  void trackWillFinishPlaying(Music* music, Track* currentTrack, Track* nextTrack, int trackNumber);
  void trackDidFinishPlaying(Music* music, Track* finishedTrack, Track* nextTrack, int trackNumber);
  void pushTracksFor(MusicSet* set);
  void pushTracks(const char* identifier, int count, MusicSet* set);
  void pushWaitTracks(const char* characterIdentifier, MusicSet* set);
  void pushTrack(const char* identifier, MusicSet* set);
  void onFinishPlaying(CCObject* sender);
  void addCutin(const char* text, TextType type);
 public:
  StaffRollScene(CCArray* maps);
  virtual ~StaffRollScene();
  void onEnterTransitionDidFinish();
};

#endif /* defined(__VOXCHRONICLE__StaffRollScene__) */
