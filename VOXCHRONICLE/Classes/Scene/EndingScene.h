//
//  EndingScene.h
//  VOXCHRONICLE
//
//  Created by giginet on 2013/2/18.
//
//

#ifndef __VOXCHRONICLE__EndingScene__
#define __VOXCHRONICLE__EndingScene__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class EndingScene :public CCLayer {
 private:
  virtual bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
  virtual void registerWithTouchDispatcher();
 public:
  EndingScene(const char* endingScript);
  ~EndingScene();
};

#endif /* defined(__VOXCHRONICLE__EndingScene__) */
