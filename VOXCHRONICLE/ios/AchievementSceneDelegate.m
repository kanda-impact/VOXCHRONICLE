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
  
  UIWindow* window = [[UIApplication sharedApplication] keyWindow];
  if ([window bounds].size.height == 568) {
    // iPhone5
    CGAffineTransform move = CGAffineTransformMakeTranslation(0, 44 * 1136.f / 960.f);
    CGAffineTransform trans = CGAffineTransformScale(move, 1.0f, 1136.f / 960.f);
    [window setTransform:trans];
  }
}

@end
