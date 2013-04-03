//
//  AchievementManager.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/4/3.
//
//

#include "AchievementManager.h"
#include "CCAchievementManager.h"

#include <boost/bind.hpp>

using namespace boost;

static AchievementManager* _manager = NULL;

AchievementManager* AchievementManager::sharedManager() {
  if (_manager == NULL) {
    _manager = new AchievementManager();
  }
  return _manager;
}

AchievementManager::AchievementManager() {
}

AchievementManager::~AchievementManager() {
}

void AchievementManager::reportAchievement(const char *identifier, float percent) {
  CCAchievementManager* manager = CCAchievementManager::sharedManager();
  manager->reportAchievement(identifier, percent, true, bind(&AchievementManager::onFinishAchievementReporting, this, _1));
}

void AchievementManager::reportAchievements(cocos2d::CCArray *identifiers, cocos2d::CCArray *percents) {
  CCAchievementManager* manager = CCAchievementManager::sharedManager();
  function<void (bool error)> f = bind(&AchievementManager::onFinishAchievementReporting, this, _1);
  manager->reportAchievements(identifiers, percents, true, f);
}

void AchievementManager::onFinishAchievementReporting(bool error) {
}