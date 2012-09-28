//
//  Character.h
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/28.
//
//

#ifndef __VOXCHRONICLE__Character__
#define __VOXCHRONICLE__Character__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class Character :public CCObject {
 private:
  CCArray* _skills;
  const char* _name;
 public:
  Character(CCArray* skills);
  ~Character();
  const char* getName();
  CCArray* getSkills();
};

#endif /* defined(__VOXCHRONICLE__Character__) */
