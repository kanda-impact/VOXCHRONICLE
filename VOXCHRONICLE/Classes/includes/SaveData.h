//
//  SaveData.h
//  VOXCHRONICLE
//
//  Created by giginet on 2013/3/2.
//
//

#ifndef __VOXCHRONICLE__SaveData__
#define __VOXCHRONICLE__SaveData__

#include <iostream>
#include <list>
#include "cocos2d.h"
#include "Map.h"
#include "Enemy.h"

using namespace std;
using namespace cocos2d;

/**
 セーブデータクラスです
 到達状況やスコアや、その他諸々がここに格納されます
 save/loadはCCUserDefaultに任せます。
 */

typedef enum {
  SaveDataCountKeyDead,
  SaveDataCountKeyTurn,
  SaveDataCountKeyDefeat,
  SaveDataCountKeyMPMiss,
  SaveDataCountKeyBoot,
  SaveDataCountKeyHitDamage,
  SaveDataCountKeyAttackDamage,
  SaveDataCountKeyDictionaryCount,
  SaveDataCountKeyNum
} SaveDataCountKey;

typedef struct {
  SaveDataCountKey key;
  int count;
  string identifier;
} AchievementInfo;

class SaveData :public CCObject {
 private:
  CCDictionary* _countDictionary;
  CCArray* _achievements;
  
  list<AchievementInfo>* _achievementInfos;
  
  void checkUnlockAchievement(SaveDataCountKey key, int value);
  void onFinishAchievementReporting(const char* identifier, bool error);
 public:
  static SaveData* sharedData();
  SaveData();
  virtual ~SaveData();
  void save();
  void load();
  int getDefeatedCount(const char* enemyIdentifier);
  void addDefeatedCountForEnemy(const char* enemyIdentifier);
  bool isClearedMap(const char* mapIdentifier);
  void setClearedForMap(const char* mapIdentifier);
  void addCountFor(SaveDataCountKey key);
  void addCountFor(SaveDataCountKey key, int value);
  int getCountFor(SaveDataCountKey key);
  bool isUnlockAchievement(const char* identifier);
  void unlockAchievement(const char* identifier);
  void setUnlockedAchievement(const char* identifier);
};

#endif /* defined(__VOXCHRONICLE__SaveData__) */
