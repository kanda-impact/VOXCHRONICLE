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
#include <boost/function.hpp>

#include "cocos2d.h"

#include "Enemy.h"

using namespace cocos2d;

class EnemyManager :public CCLayer {
 private:
  CCArray* _enemies;
  int _enemyCount;
  //Level* _level;
 public:
  virtual bool init();
  EnemyManager();
  ~EnemyManager();
  Enemy* popEnemy();
  Enemy* lotPopEnemy();
  bool isExistEnemy(int col, int row);
  CCArray* getEnemies();
  //Level* getLevel();
  //void setLevel(Level* lv);
  Enemy* enemyAt(int col, int row);
  bool removeEnemy(Enemy* enemy);
  Enemy* getNearestEnemy();
  CCArray* getFilteredEnemies(boost::function<bool (Enemy*)>filter);
  bool attackEnemy(Enemy* enemy, int attack);
  LAYER_CREATE_FUNC(EnemyManager)
};

#endif /* defined(__VOXCHRONICLE__EnemyManager__) */
