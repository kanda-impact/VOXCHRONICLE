//
//  MusicManager.h
//  VOXCHRONICLE
//
//  Created by giginet on 2013/2/4.
//
//

#ifndef __VOXCHRONICLE__MusicManager__
#define __VOXCHRONICLE__MusicManager__

#include <iostream>
#include "cocos2d.h"
#include "Music.h"
#include "MusicSet.h"
#include "EnemyManager.h"
#include "CharacterManager.h"
#include "Skill.h"

using namespace cocos2d;

typedef enum {
  MusicTrackMain = 0,
  MusicTrackCounter = 1,
  MusicTrackDrum = 2,
  MusicTrackNum = 3
} MusicTrack;

class MusicManager :public CCObject {
 private:
  int _introCount;
  int _finishCount;
  bool _isImpact;
  string _extension;
  VISS::Music* _music;
  MusicSet* _musicSet;
  EnemyManager* _enemyManager;
  CharacterManager* _characterManager;
  int calcDrumScore();
  int checkCounterNumber();
  string getTrackFileName(const char* trackName);
 public:
  MusicManager(VISS::Music* music, MusicSet* musicSet, EnemyManager* enemyManager, CharacterManager* characterManager);
  ~MusicManager();
  
  /**
   ファイルの拡張子を指定します。
   初期値は.cafです。Windows版は適宜変更してください
   @param const char* ext 拡張子
   */
  void setExtension(const char* ext);
  
  /**
   イントロトラックをまとめてセットします
   */
  void pushIntroTracks();
  
  /**
   アウトロトラックをまとめてセットします
   */
  void pushFinishTracks();
  
  /**
   無音トラックを1小節分まとめてセットします
   */
  void pushSilentTracks();
  
  /**
   次のトラックをセットします
   @param Skill* skill 次に使用するSkill
   @param SkillPerformInfo& performInfo Skillの情報を受け取るSkillPerformInfo
   */
  void pushNextTracks(Skill* skill, SkillPerformInfo& performInfo);
  
  int getIntroCount();
  void setIntroCount(int count);
  int getFinishCount();
  void setFinishCount(int count);
};

#endif /* defined(__VOXCHRONICLE__MusicManager__) */
