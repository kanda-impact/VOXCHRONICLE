//
//  AchievementSceneDelegate.m
//  VOXCHRONICLE
//
//  Created by giginet on 2013/4/3.
//
//

#import "AchievementSceneDelegate.h"
#import "ObjectAL.h"

@implementation AchievementSceneDelegate

- (void)achievementViewControllerDidFinish:(GKAchievementViewController *)viewController {
  [[OALSimpleAudio sharedInstance] playEffect:@"cancel.mp3"];
  [viewController dismissModalViewControllerAnimated:YES];
}

@end
