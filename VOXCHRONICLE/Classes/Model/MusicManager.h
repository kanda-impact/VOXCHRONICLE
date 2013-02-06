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
using namespace VISS;

typedef enum {
  MusicChannelMain = 0,
  MusicChannelCounter = 1,
  MusicChannelDrum = 2,
  MusicChannelNum = 3
} MusicChannel;

class MusicManager :public CCObject {
 private:
  int _introCount;
  int _finishCount;
  bool _isImpact;
  string _extension;
  Music* _music;
  MusicSet* _musicSet;
  EnemyManager* _enemyManager;
  CharacterManager* _characterManager;
  
  /**
   ドラムスコアを計算します。
   いわゆる空気読めるドラムシステム（KYDS）
   @return int ドラムスコア 0 ~ 4
   */
  int calcDrumScore();
  
  /**
   近くにいる敵から現在のリフの番号を取得します
   @return int リフの番号 0 ~ 3
   */
  int checkCounterNumber();
  
  /**
   ファイル名と拡張子を繋いでくれるお便利関数です
   @return string 拡張子の付いたトラック名
   */
  string getTrackFileName(const char* trackName);
 public:
  MusicManager(VISS::Music* music, MusicSet* musicSet, EnemyManager* enemyManager, CharacterManager* characterManager);
  ~MusicManager();
  
  /**
   ファイルの拡張子を指定します。
   初期値は.cafです。Windows版は適宜変更してください(oggなど)
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
  
  /**
   現在のイントロ小節数を取得します
   @return int イントロ小節数
   */
  int getIntroCount();
  
  /**
   イントロ小節数を変更します
   @param int count イントロ小節数
   */
  void setIntroCount(int count);
  
  /**
   現在のアウトロ小節数を取得します
   @return int アウトロ小節数
   */
  int getFinishCount();
  
  /**
   アウトロ小節数を変更します
   @param int count アウトロ小節数
   */
  void setFinishCount(int count);
  
  /**
   Musicを取得します
   @return Music* Music
   */
  Music* getMusic();
  
  /**
   MusicSetを取得します
   @return MusicSet* MusicSet
   */
  MusicSet* getMusicSet();
  
  /**
   Musicを設定します
   @param Music* music
   */
  void setMusic(Music* music);
  
  /**
   MusicSetを設定します
   @param MusicSet* set
   */
  void setMusicSet(MusicSet* set);
};

#endif /* defined(__VOXCHRONICLE__MusicManager__) */