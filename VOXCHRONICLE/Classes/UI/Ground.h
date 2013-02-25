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

class Ground :public CCSprite {
 private:
  int _frameCount;
  int _currentFrame;
  std::string _prefix;
 public:
  Ground(const char* prefix, int frameCount);
  void nextFrame();
};

#endif /* defined(__VOXCHRONICLE__Ground__) */
