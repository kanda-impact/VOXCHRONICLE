//
//  MainMenuScene.h
//  VOXCHRONICLE
//
//  Created by giginet on 2013/3/3.
//
//

#ifndef __VOXCHRONICLE__MainMenuScene__
#define __VOXCHRONICLE__MainMenuScene__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class MainMenuScene :public CCLayer {
 private:
  void onStartPressed(CCObject* sender);
  void onTutorialPressed(CCObject* sender);
  void onExtraPressed(CCObject* sender);
  void onBackPressed(CCObject* sender);
  bool _fromTitle;
 public:
  MainMenuScene(bool fromTitle);
  void onEnterTransitionDidFinish();
};

#endif /* defined(__VOXCHRONICLE__MainMenuScene__) */
