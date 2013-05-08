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
  [viewController dismissModalViewControllerAnimated:NO];
  
  UIWindow* window = [[UIApplication sharedApplication] keyWindow];
  if ([window bounds].size.height == 568) {
    // iPhone5
    UIView* glView = [window.subviews objectAtIndex:0];
    CGAffineTransform transform = glView.transform;
    CGAffineTransform move = CGAffineTransformTranslate(transform, 44 * 1136.f / 960.f, 0);
    CGAffineTransform trans = CGAffineTransformScale(move, 1136.f / 960.f, 1.0f);
    [glView setTransform:trans];
  }
}

@end
