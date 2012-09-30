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
#include <vector>

using namespace std;

class Level {
 private:
  int _level;
 public:
  Level();
  int getLevel();
  vector<const char*> getEnemies();
};

#endif /* defined(__VOXCHRONICLE__Level__) */
