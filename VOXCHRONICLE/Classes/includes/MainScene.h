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

#include "EnemyManager.h"
#include "CharacterManager.h"
#include "MapSelector.h"
#include "MessageWindow.h"
#include "MusicSet.h"
#include "QTETrigger.h"
#include "MusicManager.h"
#include "Skin.h"

typedef enum {
  VCStateIntro,
  VCStateMain,
  VCStateGameOver,
  VCStateFinish,
  VCStateBoss,
  VCStateMapSelect,
  VCStateQTEWait,
  VCStateQTEFinish,
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
  EnemyManager* _enemyManager;
  CharacterManager* _characterManager;
  MapSelector* _mapSelector;
  MessageWindow* _messageWindow;
  CCSprite* _focus;
  QTETrigger* _qteTrigger;
  Skin* _skin;
  
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
  void changeSkin(Skin* newSkin, bool crossFade);
  
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
