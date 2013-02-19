//
//  Skin.h
//  VOXCHRONICLE
//
//  Created by giginet on 2013/2/19.
//
//

#ifndef __VOXCHRONICLE__Skin__
#define __VOXCHRONICLE__Skin__

#include <iostream>
#include "cocos2d.h"
#include "Ground.h"
#include "StatusLayer.h"

using namespace cocos2d;

class Skin :public CCObject {
 private:
  Ground* _ground;
  StatusLayer* _statusLayer;
 public:
  Skin(const char* scriptName);
  ~Skin();
};

#endif /* defined(__VOXCHRONICLE__Skin__) */
