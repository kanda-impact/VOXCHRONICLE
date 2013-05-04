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

#include "KWAlertDelegate.h"

using namespace cocos2d;

class ResultScene :public CCLayer, public KWAlertDelegate {
 private:
  bool _isAppeard;
  virtual void registerWithTouchDispatcher();
  virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
  CCMenu* _backMenu;
  PlayLog* _log;
 public:
  virtual bool init();
  ~ResultScene();
  void setPlayLog(PlayLog* log);
  CREATE_FUNC(ResultScene);
  void buildUI();
  virtual void onEnterTransitionDidFinish();
  void onBackButtonPressed(CCObject* sender);
  virtual void clickedButtonAtIndex(KWAlert* alert, int index);
};

#endif /* defined(__VOXCHRONICLE__ResultScene__) */
