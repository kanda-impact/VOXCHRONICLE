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
  void goToNextScene(CCObject* sender);
 public:
  EndingScene(const char* endingScript);
  ~EndingScene();
};

#endif /* defined(__VOXCHRONICLE__EndingScene__) */
