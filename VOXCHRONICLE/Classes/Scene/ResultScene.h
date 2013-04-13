//
//  ResultScene.h
//  VOXCHRONICLE
//
//  Created by giginet on 2013/4/13.
//
//

#ifndef __VOXCHRONICLE__ResultScene__
#define __VOXCHRONICLE__ResultScene__

#include <iostream>

#include "cocos2d.h"
#include "PlayLog.h"

using namespace cocos2d;

class ResultScene :public CCLayer {
  PlayLog* _log;
 public:
  virtual bool init();
  ~ResultScene();
  void setPlayLog(PlayLog* log);
  CREATE_FUNC(ResultScene);
  void buildUI();
  void onBackButtonPressed(CCObject* sender);
};

#endif /* defined(__VOXCHRONICLE__ResultScene__) */
