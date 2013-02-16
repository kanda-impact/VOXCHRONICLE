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
#include "StatusLayer.h"
#include "MusicSet.h"
#include "QTETrigger.h"
#include "Ground.h"
#include "MusicManager.h"

typedef enum {
  VCStateIntro,
  VCStateMain,
  VCStateGameOver,
  VCStateFinish,
  VCStateBoss,
  VCStateQTE, // QTE前奏用
  VCStateQTEWait, // QTEウェイト用
  VCStateQTEFinish,  // QTE寸止め用
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
  bool _isLevelUped;
  SkillPerformInfo _currentSkillInfo;
  Controller* _controller;
  EnemyManager* _enemyManager;
  CharacterManager* _characterManager;
  MapSelector* _mapSelector;
  MessageWindow* _messageWindow;
  StatusLayer* _statusLayer;
  CCSprite* _focus;
  QTETrigger* _qteTrigger;
  
  Ground* _ground;
  Level* _level;
  Map* _map;
  VCState _state;
  
  MusicManager* _musicManager;
  
  CCSet* _pausedTargets;
  
  void onEnterTransitionDidFinish();
  
  void trackDidBack(Music* music, Track* currentTrack, int trackNumber);
  void trackWillFinishPlaying(Music* music, Track* currentTrack, Track* nextTrack, int trackNumber);
  void trackDidFinishPlaying(Music* music, Track* finishedTrack, Track* nextTrack, int trackNumber);
  
  void updateGUI();
  void onGameOver();
  
  void update(float dt);
  bool checkLevelUp();
  
  void removeNode(CCNode *node);
  
  void updateFocus();
  void addDamageEffect();
  void changeMap(Map* nextMap);
  
  //void pushIntroTracks();
  //void pushFinishTracks();
  
  void startBossBattle();
  void gotoNextStage();
  void onFinishTracksCompleted();
  
 public:
  virtual bool init(Map* map);
  virtual bool init();
  ~MainScene();
  void setPause(bool pause);
  Music* getMusic();
  Map* getMap();
  VCState getState();
  
  CREATE_FUNC(MainScene);
};

#endif /* defined(__VOXCHRONICLE__MainScene__) */
