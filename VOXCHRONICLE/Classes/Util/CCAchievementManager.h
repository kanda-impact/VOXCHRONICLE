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
  void reportAchievement(const char *identifier, float percent, function<void (bool error)> onComplete);
  void reportAchievements(CCArray *identifiers, CCArray *percents, function<void (bool error)> onComplete);
};

#endif /* defined(__VOXCHRONICLE__GKAchievementManager__) */