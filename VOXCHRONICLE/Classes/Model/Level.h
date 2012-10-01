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

using namespace std;

class Level {
 private:
  int _level;
  list<pair<string, int> > _enemyTable;
 public:
  Level(int level);
  int getLevel();
  list<pair<string, int> > getEnemyTable();
  void setEnemyTable(list<pair<string, int> > table);
};

#endif /* defined(__VOXCHRONICLE__Level__) */
