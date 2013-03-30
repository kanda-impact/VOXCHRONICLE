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
#include <queue>
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class SEManager :public CCObject {
 private:
  float _currentDelay;
  queue< pair<string, float> >* _seQueue;
  void playEffect();
 public:
  static SEManager* sharedManager();
  void update(float delay);
  SEManager();
  ~SEManager();
  void registerEffect(const char* filename);
  void registerEffect(const char* filename, float delay);
};

#endif /* defined(__VOXCHRONICLE__SEManager__) */
