//
//  Enemy.h
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/28.
//
//

#ifndef __VOXCHRONICLE__Enemy__
#define __VOXCHRONICLE__Enemy__

#include <iostream>
#include "CCSprite.h"

using namespace cocos2d;

class Enemy : public CCSprite {
 private:
  int _hp;
  int _mp;
  int _row;
  int _col;
  void update(float dt);
 public:
  static Enemy* create(const char* filename);
  Enemy();
  ~Enemy();
  float getRow();
  void setRow(float r);
  int getCol();
  void setCol(int c);
  float bottomLine();
};

#endif /* defined(__VOXCHRONICLE__Enemy__) */
