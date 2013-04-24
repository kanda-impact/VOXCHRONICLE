//
//  TutorialScene.h
//  VOXCHRONICLE
//
//  Created by giginet on 2013/3/3.
//
//

#ifndef __VOXCHRONICLE__TutorialScene__
#define __VOXCHRONICLE__TutorialScene__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class TutorialLayer :public CCLayer {
 private:
  void onTutorialButtonPressed(CCObject* sender);
  void onBackButtonPressed(CCObject* sender);
 public:
  virtual void onEnterTransitionDidFinish();
  virtual bool init();
  CREATE_FUNC(TutorialLayer);
};

#endif /* defined(__VOXCHRONICLE__TutorialScene__) */
