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

#include "MainScene.h"

using namespace cocos2d;

class FreePlayScene :public CCLayer {
 private:
  MainBackScene _backScene;
  void onMenuItemPressed(CCObject* sender);
 public:
  virtual bool init(const char* script, bool unlock);
  virtual void onEnterTransitionDidFinish();
  virtual void onBackButtonPressed();
  static cocos2d::CCScene* scene(const char* script, bool unlock);
  static FreePlayScene* create(const char* script, bool unlock);
};

#endif /* defined(__VOXCHRONICLE__FreePlayScene__) */
