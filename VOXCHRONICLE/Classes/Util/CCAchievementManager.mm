//
//  GKAchievementManager.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/4/1.
//
//

#include "CCAchievementManager.h"
#import <GameKit/GameKit.h>

static CCAchievementManager* _manager = NULL;

CCAchievementManager* CCAchievementManager::sharedManager() {
  if (_manager == NULL) {
    _manager = new CCAchievementManager();
  }
  return _manager;
}

CCAchievementManager::CCAchievementManager() {
  
}

CCAchievementManager::~CCAchievementManager() {
}

void CCAchievementManager::authenticate() {
  
}

void CCAchievementManager::reportAchievement(const char *identifier, float percent) {
  GKAchievement* achievement = [[GKAchievement alloc] initWithIdentifier:[NSString stringWithCString:identifier encoding:NSUTF8StringEncoding]];
  achievement.percentComplete = percent;
  achievement.showsCompletionBanner = YES;
  [achievement reportAchievementWithCompletionHandler:^(NSError *error) {
    NSLog(@"report = %@", error);
  }];
}

void CCAchievementManager::reportAchievements(cocos2d::CCArray *identifiers, cocos2d::CCArray *percents) {
  NSArray* achievements = [NSArray array];
  
  for (int i = 0; i < identifiers->count(); ++i) {
    const char* identifierString = ((CCString*)identifiers->objectAtIndex(0))->getCString();
    GKAchievement* achievement = [[GKAchievement alloc] initWithIdentifier:[NSString stringWithCString:identifierString encoding:NSUTF8StringEncoding]];
    achievement.showsCompletionBanner = YES;
    float percent = (float)((CCInteger*)percents->objectAtIndex(i))->getValue() / 100.0;
    achievement.percentComplete = percent;
  }
  [GKAchievement reportAchievements:achievements
              withCompletionHandler:^(NSError *error) {
              }];
}

void CCAchievementManager::loadAhievements(function<void (CCArray* achievements, bool error)> onCompleter) {
}