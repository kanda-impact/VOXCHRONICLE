//
//  Controller.h
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/8.
//
//

#ifndef __VOXCHRONICLE__Controller__
#define __VOXCHRONICLE__Controller__

#include <iostream>
#include "cocos2d.h"

class Controller : public cocos2d::CCNode {
 private:
  cocos2d::CCArray* _triggers;

public:
  static Controller* create();
  ~Controller();
  Controller();
};

#endif /* defined(__VOXCHRONICLE__Controller__) */
