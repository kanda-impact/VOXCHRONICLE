//
//  EnemyManager.h
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/28.
//
//

#ifndef __VOXCHRONICLE__EnemyManager__
#define __VOXCHRONICLE__EnemyManager__

#include <iostream>

#include "cocos2d.h"

#include "Enemy.h"

using namespace cocos2d;

class EnemyManager {
 private:
  CCArray* _enemies;
  //Level* _level;
 public:
  EnemyManager();
  ~EnemyManager();
  Enemy* popEnemy();
  bool isExistEnemy(int col, int row);
  CCArray* getEnemies();
  //Level* getLevel();
  //void setLevel(Level* lv);
  Enemy* enemyAt(int col, int row);
};

#endif /* defined(__VOXCHRONICLE__EnemyManager__) */
