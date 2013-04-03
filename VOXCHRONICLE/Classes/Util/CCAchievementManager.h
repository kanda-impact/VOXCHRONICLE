//
//  GKAchievementManager.h
//  VOXCHRONICLE
//
//  Created by giginet on 2013/4/1.
//
//

#ifndef __VOXCHRONICLE__GKAchievementManager__
#define __VOXCHRONICLE__GKAchievementManager__

#include <iostream>
#include <boost/function.hpp>
#include "cocos2d.h"

using namespace cocos2d;
using namespace boost;

class CCAchievementManager :public CCObject {
 private:
  CCAchievementManager();
  ~CCAchievementManager();
 public:
  static CCAchievementManager* sharedManager();
  void reportAchievement(const char *identifier, float percent);
  void reportAchievements(CCArray *identifiers, CCArray *percents);
  void loadAhievements(function<void (CCArray* achievements, bool error)> onComplete);
  void authenticate();
};

#endif /* defined(__VOXCHRONICLE__GKAchievementManager__) */