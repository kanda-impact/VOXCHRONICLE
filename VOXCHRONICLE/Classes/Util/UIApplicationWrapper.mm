//
//  UIApplicationWrapper.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/4/30.
//
//

#include "UIApplicationWrapper.h"
#import <UIKit/UIKit.h>

UIApplicationWrapper* UIApplicationWrapper::_instance = NULL;

UIApplicationWrapper* UIApplicationWrapper::sharedApplication() {
  if (!_instance) {
    _instance = new UIApplicationWrapper();
  }
  return _instance;
}

void UIApplicationWrapper::setIdleTimerDisabled(bool disable) {
  [[UIApplication sharedApplication] setIdleTimerDisabled:disable];
}