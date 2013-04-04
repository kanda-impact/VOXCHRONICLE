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
#include "cocos2d.h"
#include "Map.h"
#include "Enemy.h"

using namespace cocos2d;

/**
 セーブデータクラスです
 到達状況やスコアや、その他諸々がここに格納されます
 save/loadはCCUserDefaultに任せます。
 */

typedef enum {
  SaveDataCountKeyDead,
  SaveDataCountKeyBeat,
  SaveDataCountDefeat,
  SaveDataCountKeyMPMiss,
  SaveDataCountKeyBoot,
  SaveDataCountKeyNum
} SaveDataCountKey;

class SaveData :public CCObject {
 private:
  CCDictionary* _countDictionary;
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
  int getCountFor(SaveDataCountKey key);
};

#endif /* defined(__VOXCHRONICLE__SaveData__) */
