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
  int _frameCount;
  std::string _prefix;
  CCSprite* _background;
  void setAnimaton(int frameCount);
 public:
  Ground(const char* prefix, int frameCount);
  void play();
  void stop();
};

#endif /* defined(__VOXCHRONICLE__Ground__) */
