//
//  EnemyManager.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/28.
//
//

#include <boost/random.hpp>

#include "EnemyManager.h"

using namespace boost;

EnemyManager::EnemyManager() {
  _enemies = CCArray::create();
  _enemies->retain();
  mt19937 gen( static_cast<unsigned long>(time(0)) );
  uniform_smallint<> dst( 0, 2 );
  variate_generator<
  mt19937&, uniform_smallint<>
  > rand( gen, dst );
}

EnemyManager::~EnemyManager() {
  _enemies->release();
}

Enemy* EnemyManager::popEnemy() {
  Enemy* enemy = Enemy::create("enemy.png");
  int col = rand() % 3;
  std::cout << "col : " << col << std::endl;
  enemy->setCol(col);
  _enemies->addObject(enemy);
  return enemy;
}

bool EnemyManager::isExistEnemy(int col, int row) {
  return (this->enemyAt(col, row) != NULL);
}

Enemy* EnemyManager::enemyAt(int col, int row) {
  CCObject* obj = NULL;
  CCARRAY_FOREACH(_enemies, obj) {
    Enemy* enemy = (Enemy*)obj;
    if (enemy->getRow() == row && enemy->getCol() == col) {
      return enemy;
    }
  }
  return NULL;
}

CCArray* EnemyManager::getEnemies() {
  return _enemies;
}

bool EnemyManager::removeEnemy(Enemy* enemy) {
  if (_enemies->containsObject(enemy)) {
    _enemies->removeObject(enemy);
    return true;
  }
  return false;
}