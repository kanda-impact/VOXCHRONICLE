//
//  AchievementManager.h
//  VOXCHRONICLE
//
//  Created by giginet on 2013/4/3.
//
//

#ifndef __VOXCHRONICLE__AchievementManager__
#define __VOXCHRONICLE__AchievementManager__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class AchievementManager :public CCObject {
 private:
  void onFinishAchievementReporting(bool error);
 public:
  static AchievementManager* sharedManager();
  AchievementManager();
  virtual ~AchievementManager();
  void reportAchievement(const char* identifier, float percent);
  void reportAchievements(CCArray* identifiers, CCArray* percents);
};

#endif /* defined(__VOXCHRONICLE__AchievementManager__) */
