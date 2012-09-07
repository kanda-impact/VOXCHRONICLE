//
//  LogoScene.h
//  VOXCHRONICLE
//
//  Created by giginet on 2012/8/27.
//
//

#ifndef __VOXCHRONICLE__LogoScene__
#define __VOXCHRONICLE__LogoScene__

#include <iostream>
#include "cocos2d.h"

class LogoScene : public cocos2d::CCLayer {
 private:
  virtual bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
  virtual void nextScene();
  virtual void registerWithTouchDispatcher();

public:
  virtual bool init();
  static cocos2d::CCScene* scene();
  
  LAYER_CREATE_FUNC(LogoScene);
};

#endif /* defined(__VOXCHRONICLE__LogoScene__) */
