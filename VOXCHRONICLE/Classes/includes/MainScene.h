//
//  MainScene.h
//  VOXCHRONICLE
//
//  Created by giginet on 2012/8/28.
//
//

#ifndef __VOXCHRONICLE__MainScene__
#define __VOXCHRONICLE__MainScene__

#include <iostream>
#include "cocos2d.h"
#include "Track.h"
#include "Music.h"
#include "Map.h"
#include "Level.h"

#include "Controller.h"
#include "EnemyManager.h"
#include "CharacterManager.h"
#include "MapSelector.h"
#include "MessageWindow.h"

typedef enum {
  VCStateIntro,
  VCStateMain,
  VCStateGameOver,
  VCStateBoss,
  VCStateStageSelect,
  VCStateEnding
} VCState;

using namespace VISS;
using namespace cocos2d;

class MainScene : public CCLayer {
 private:
  int _preLevel;
  int _turnCount;
  int _mapTurnCount;
  Music* _music;
  Controller* _controller;
  EnemyManager* _enemyManager;
  CharacterManager* _characterManager;
  MapSelector* _mapSelector;
  MessageWindow* _messageWindow;
  
  CCLabelTTF* _levelLabel;
  CCLabelTTF* _hpLabel;
  CCLabelTTF* _mpLabel;
  CCLabelTTF* _expLabel;
  CCLabelTTF* _nextExpLabel;
  CCLabelTTF* _mapLabel;
  
  Level* _level;
  Map* _map;
  VCState _state;
  
  void onEnterTransitionDidFinish();
  
  void trackDidBack(Music* music, Track* currentTrack, int trackNumber);
  void trackWillFinishPlaying(Music* music, Track* currentTrack, Track* nextTrack, int trackNumber);
  void trackDidFinishPlaying(Music* music, Track* finishedTrack, Track* nextTrack, int trackNumber);
  
  void updateGUI();
  void pushInitialTracks(Map* map);
  
  void addGameOverButtons();
  void replayButtonPressed();
  void titleButtonPressed();
  void onGameOver();
  
  void update(float dt);
  bool checkLevelUp();
  
 public:
  virtual bool init();
  ~MainScene();
  
  CREATE_FUNC(MainScene);
};

#endif /* defined(__VOXCHRONICLE__MainScene__) */
