//
//  FreePlayScene.h
//  VOXCHRONICLE
//
//  Created by giginet on 1/9/13.
//
//

#ifndef __VOXCHRONICLE__FreePlayScene__
#define __VOXCHRONICLE__FreePlayScene__

#include <iostream>

#include "cocos2d.h"

using namespace cocos2d;

class FreePlayScene :public CCLayer {
 private:
  void onMenuItemPressed(CCObject* sender);
 public:
  virtual bool init(const char* script);
  virtual void onEnterTransitionDidFinish();
  static cocos2d::CCScene* scene(const char* script);
  static FreePlayScene* create(const char* script);
};

#endif /* defined(__VOXCHRONICLE__FreePlayScene__) */
