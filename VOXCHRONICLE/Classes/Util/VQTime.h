//
//  VQTime.h
//  VOXCHRONICLE
//
//  Created by giginet on 2013/4/6.
//
//

#ifndef __VOXCHRONICLE__VQTime__
#define __VOXCHRONICLE__VQTime__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

// NSDateのC++ Wrapperです

class VQTime :public CCObject {
 public:
  static VQTime* sharedTime();
  int getCurrentHour();
};

#endif /* defined(__VOXCHRONICLE__VQTime__) */
