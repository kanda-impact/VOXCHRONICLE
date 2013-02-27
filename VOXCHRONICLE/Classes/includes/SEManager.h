//
//  SEManager.h
//  VOXCHRONICLE
//
//  Created by giginet on 2013/2/27.
//
//

#ifndef __VOXCHRONICLE__SEManager__
#define __VOXCHRONICLE__SEManager__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class SEManager :public CCObject {
 private:
  CCArray* _seQueue;
  void playEffect(CCObject* sender);
 public:
  static SEManager* sharedManager();
  SEManager();
  ~SEManager();
  void registerEffect(const char* filename);
};

#endif /* defined(__VOXCHRONICLE__SEManager__) */
