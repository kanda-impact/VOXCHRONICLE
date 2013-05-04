//
//  InitialScene.h
//  VOXCHRONICLE
//
//  Created by giginet on 2013/5/4.
//
//

#ifndef __VOXCHRONICLE__InitialScene__
#define __VOXCHRONICLE__InitialScene__

#include <iostream>
#include "cocos2d.h"
#include "KWAlertDelegate.h"

using namespace cocos2d;

class InitialScene :public CCLayer, KWAlertDelegate {
 public:
  virtual bool init();
  virtual void clickedButtonAtIndex(KWAlert* alert, int index);
  void onGotoTutorial();
  void onEnterTransitionDidFinish();
  CREATE_FUNC(InitialScene);
};

#endif /* defined(__VOXCHRONICLE__InitialScene__) */
