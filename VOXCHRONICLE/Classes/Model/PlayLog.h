//
//  PlayLog.h
//  VOXCHRONICLE
//
//  Created by giginet on 2013/4/7.
//
//

#ifndef __VOXCHRONICLE__PlayLog__
#define __VOXCHRONICLE__PlayLog__

#include <iostream>
#include "SaveData.h"
#include "cocos2d.h"
#include <map>
#include <list>

using namespace std;
using namespace cocos2d;

typedef enum {
  PlayLogKeyMaxRepeatChange,
  PlayLogKeyMaxDefeat,
  PlayLogKeyVOXAttack,
  PlayLogKeyLSKAttack,
  PlayLogKeyRun,
  PlayLogKeyTurn,
  PlayLogKeyMaxRepeat,
  PlayLogKeyNum
} PlayLogKey;

class PlayLog :public CCObject {
 private:
  map<int, int>* _count;
  list<AchievementInfo>* _achievementInfos;
  void checkAchievement(PlayLogKey key, int value);
 public:
  PlayLog();
  virtual ~PlayLog();
  void addCount(PlayLogKey key);
  int getCount(PlayLogKey key);
  void setCount(PlayLogKey key, int value);
  void setGraterCount(PlayLogKey key, int value);
  void setLesserCount(PlayLogKey key, int value);
};

#endif /* defined(__VOXCHRONICLE__PlayLog__) */
