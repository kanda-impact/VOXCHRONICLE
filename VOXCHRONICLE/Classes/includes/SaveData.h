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

using namespace cocos2d;

/**
 セーブデータクラスです
 到達状況やスコアや、その他諸々がここに格納されます
 save/loadはCCUserDefaultに任せます。
 */

class SaveData :public CCObject {
 private:
  bool _dirty;
  CCArray* _clearedMaps; // マップのクリア状態保存
  CCDictionary* _defeatedCount; // 討伐モンスターカウント
 public:
  static SaveData* sharedData();
  SaveData();
  virtual ~SaveData();
  bool save();
  bool load();
  CCArray* getClearedMaps();
  void markClearedForMap(Map* map);
};

#endif /* defined(__VOXCHRONICLE__SaveData__) */
