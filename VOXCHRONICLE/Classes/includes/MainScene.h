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
#include "PlayLog.h"

#include "EffectLayer.h"

typedef enum {
  VCStateIntro,
  VCStateMain,
  VCStateGameOver,
  VCStateFinish,
  VCStateBoss,
  VCStateWindow,
  VCStateMapSelect,
  VCStateQTEWait,
  VCStateQTEFinish,
  VCStateEnding
} VCState;

typedef enum {
  MainBackSceneTitle,
  MainBackSceneMainMenu,
  MainBackSceneTutorial,
  MainBackSceneFreePlay,
  MainBackSceneSoundTest,
  MainBackSceneDebug
} MainBackScene;

using namespace VISS;
using namespace cocos2d;

class MainScene : public CCLayer {
 private:
  int _preLevel;
  int _mapTurnCount;
  int _initialLevel;
  bool _isLevelUped;
  bool _isContinue;
  MainBackScene _backScene;
  SkillPerformInfo _currentSkillInfo;
  EnemyManager* _enemyManager;
  CharacterManager* _characterManager;
  MapSelector* _mapSelector;
  MessageWindow* _messageWindow;
  QTETrigger* _qteTrigger;
  Skin* _skin;
  EffectLayer* _effectLayer;
  PlayLog* _log;
  
  Level* _level;
  Map* _map;
  VCState _state;
  
  MusicManager* _musicManager;
  
  void onEnterTransitionDidFinish();
  virtual void onExit();
  
  void trackDidBack(Music* music, Track* currentTrack, int trackNumber);
  void trackWillFinishPlaying(Music* music, Track* currentTrack, Track* nextTrack, int trackNumber);
  void trackDidFinishPlaying(Music* music, Track* finishedTrack, Track* nextTrack, int trackNumber);
  
  void updateGUI();
  void onGameOver();
  
  void update(float dt);
  bool checkLevelUp();
  
  void addDamageEffect();
  void changeMap(Map* nextMap);
  void changeMap(Map* nextMap, int initialLevel);
  void changeMusic(MusicSet* mSet, bool enablePreload);
  
  void startBossBattle();
  void gotoNextStage();
  void onFinishTracksCompleted();
  void changeSkin(Skin* newSkin, bool crossFade);
  
  virtual bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
  virtual void registerWithTouchDispatcher();
  
 public:
  virtual bool init(Map* map, int initialLevel);
  virtual bool init(Map* map);
  virtual bool init();
  bool isBossBattle();
  ~MainScene();
  void setPause(bool pause);
  Music* getMusic();
  Map* getMap();
  VCState getState();
  
  PlayLog* getPlayLog();
  void setPlayLog(PlayLog* log);
  
  void teardown();
  
  void setBackScene(MainBackScene backScene);
  
  void setLevel(Level* lv);
  void setIsContinue(bool c);
  
  CREATE_FUNC(MainScene);
};

#endif /* defined(__VOXCHRONICLE__MainScene__) */
