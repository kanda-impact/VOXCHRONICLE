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
#include "LogoScene.h"

class LogoScene : public cocos2d::CCLayer {
public:
  virtual bool init();
  static cocos2d::CCScene* scene();
  
  void menuCloseCallback(cocos2d::CCObject* pSender);
  
  LAYER_CREATE_FUNC(LogoScene);
};

#endif /* defined(__VOXCHRONICLE__LogoScene__) */
