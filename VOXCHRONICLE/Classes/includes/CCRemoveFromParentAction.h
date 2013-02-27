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

class CC_DLL CCRemoveFromParentAction :public CCActionInstant {
public:
  static CCRemoveFromParentAction* create();
  virtual void update(float time);
};

#endif /* defined(__VOXCHRONICLE__CCRemoveFromParentAction__) */
