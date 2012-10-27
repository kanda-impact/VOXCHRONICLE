//
//  Level.h
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/29.
//
//

#ifndef __VOXCHRONICLE__Level__
#define __VOXCHRONICLE__Level__

#include <iostream>
#include <list>
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class Level :public CCObject {
 private:
  int _level;
  list<pair<string, int> > _enemyTable;
  float _enemyPopRate;
 public:
  Level(int level);
  int getLevel();
  float getEnemyPopRate();
  void setEnemyPopRate(float rate);
  list<pair<string, int> > getEnemyTable();
  void setEnemyTable(list<pair<string, int> > table);
};

#endif /* defined(__VOXCHRONICLE__Level__) */
