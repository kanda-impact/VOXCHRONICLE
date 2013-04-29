//
//  UIApplicationWrapper.h
//  VOXCHRONICLE
//
//  Created by giginet on 2013/4/30.
//
//

#ifndef __VOXCHRONICLE__UIApplicationWrapper__
#define __VOXCHRONICLE__UIApplicationWrapper__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class UIApplicationWrapper :public CCObject {
 private:
  static UIApplicationWrapper* _instance;
 public:
  static UIApplicationWrapper* sharedApplication();
  void setIdleTimerDisabled(bool disable);
};

#endif /* defined(__VOXCHRONICLE__UIApplicationWrapper__) */
