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
#include "Skill.h"
#include "Level.h"
#include "CharacterManager.h"

using namespace cocos2d;

class EnemyManager :public CCLayer {
 private:
  CCArray* _enemies;
  vector<bool>* _enemyPopLots;
  Level* _level;
  CCArray* _enemiesQueue;
  CCArray* createEnemyQueue();
 public:
  virtual bool init();
  EnemyManager();
  ~EnemyManager();
  Enemy* popEnemy();
  Enemy* lotPopEnemy();
  bool isExistEnemy(int col, int row);
  CCArray* getEnemies();
  Level* getLevel();
  void setLevel(Level* lv);
  Enemy* enemyAt(int col, int row);
  bool removeEnemy(Enemy* enemy);
  Enemy* getNearestEnemy();
  CCArray* getFilteredEnemies(boost::function<bool (int, float)>filter);
  bool attackEnemy(Enemy* enemy, int attack);
  CCArray* performSkill(Skill* skill, CharacterManager* characterManager);
  CREATE_FUNC(EnemyManager)
};

#endif /* defined(__VOXCHRONICLE__EnemyManager__) */
