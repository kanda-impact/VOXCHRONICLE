//
//  Controller.h
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/8.
//
//

#ifndef __VOXCHRONICLE__Controller__
#define __VOXCHRONICLE__Controller__

#include <iostream>
#include "cocos2d.h"

class Controller : public cocos2d::CCLayer {
 private:
  cocos2d::CCArray* _triggers;
  virtual bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
  virtual void registerWithTouchDispatcher();

public:
  virtual bool init();
  ~Controller();
  Controller();
  void resetAllTriggers();
  LAYER_CREATE_FUNC(Controller)
};

#endif /* defined(__VOXCHRONICLE__Controller__) */
