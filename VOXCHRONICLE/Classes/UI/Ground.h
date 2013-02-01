//
//  Ground.h
//  VOXCHRONICLE
//
//  Created by giginet on 2013/2/1.
//
//

#ifndef __VOXCHRONICLE__Ground__
#define __VOXCHRONICLE__Ground__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class Ground :public CCNode {
 private:
  CCSprite* _background;
 public:
  Ground(const char* prefix);
  void play();
  void stop();
};

#endif /* defined(__VOXCHRONICLE__Ground__) */
