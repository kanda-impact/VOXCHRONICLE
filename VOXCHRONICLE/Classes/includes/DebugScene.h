//
//  DebugScene.h
//  VOXCHRONICLE
//
//  Created by giginet on 1/9/13.
//
//

#ifndef __VOXCHRONICLE__DebugScene__
#define __VOXCHRONICLE__DebugScene__

#include <iostream>

#include "cocos2d.h"

using namespace cocos2d;

class DebugScene :public CCLayer {
 private:
  void onMenuItemPressed(CCObject* sender);
 public:
  virtual bool init();
  virtual void onEnterTransitionDidFinish();
  static cocos2d::CCScene* scene();
  CREATE_FUNC(DebugScene);
};

#endif /* defined(__VOXCHRONICLE__DebugScene__) */
