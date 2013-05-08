//
//  AchievementScene.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/4/3.
//
//

#include "AchievementScene.h"
#include <UIKit/UIKit.h>
#include <GameKit/GameKit.h>
#import "AchievementSceneDelegate.h"

bool AchievementScene::init() {
  if (!CCLayer::init()) {
    return false;
  }
  
  UIWindow* window = [[UIApplication sharedApplication] keyWindow];
  UIViewController* controller = window.rootViewController;
  GKAchievementViewController* avc = [[[GKAchievementViewController alloc] init] autorelease];
  // ToDo delegateオブジェクトがメモリリークしてるけどあとで直す
  // delegateはweakプロパティになってるから云々
  AchievementSceneDelegate* delegate = [[AchievementSceneDelegate alloc] init];
  avc.achievementDelegate = delegate;
  [controller presentModalViewController:avc animated:NO];
  
  return true;
}

AchievementScene::~AchievementScene() {
  
}