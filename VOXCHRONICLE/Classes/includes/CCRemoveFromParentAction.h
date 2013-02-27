//
//  CCRemoveFromParentAction.h
//  VOXCHRONICLE
//
//  Created by giginet on 2013/2/27.
//
//

#ifndef __VOXCHRONICLE__CCRemoveFromParentAction__
#define __VOXCHRONICLE__CCRemoveFromParentAction__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

/**
 This class is ported from CCRemoveFromParentAction on Kobold2D.
*/

class CCRemoveFromParentAction :public CCActionInstant {
 public:
  virtual void startWithTarget(cocos2d::CCNode *pTarget);
};

#endif /* defined(__VOXCHRONICLE__CCRemoveFromParentAction__) */
