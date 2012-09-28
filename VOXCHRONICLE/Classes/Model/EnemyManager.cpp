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

bool EnemyManager::init() {
  if (!CCLayer::init()) {
    return false;
  }
  _enemies = CCArray::create();
  _enemies->retain();
  mt19937 gen( static_cast<unsigned long>(time(0)) );
  uniform_smallint<> dst( 0, 2 );
  variate_generator<
  mt19937&, uniform_smallint<>
  > rand( gen, dst );
  _enemyCount = 0;
  return true;
}

EnemyManager::EnemyManager() {
}

EnemyManager::~EnemyManager() {
  _enemies->release();
}

Enemy* EnemyManager::popEnemy() {
  Enemy* enemy = Enemy::create("enemy.png");
  int col = rand() % 3;
  enemy->setCol(col);
  _enemies->addObject(enemy);
  this->addChild(enemy);
  return enemy;
}

Enemy* EnemyManager::lotPopEnemy() {
  _enemyCount += rand() % 20;
  if (_enemyCount > 50) {
    _enemyCount = 0;
    return this->popEnemy();
  }
  return NULL;
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
    this->removeChild(enemy, true);
    _enemies->removeObject(enemy);
    return true;
  }
  return false;
}

Enemy* EnemyManager::getNearestEnemy() {
  CCObject* obj = NULL;
  Enemy* minEnemy = NULL;
  CCARRAY_FOREACH(_enemies, obj) {
    Enemy* enemy = (Enemy*)obj;
    if (!minEnemy || enemy->getRow() < minEnemy->getRow() || (enemy->getRow() == minEnemy->getRow() && enemy->getCol() < minEnemy->getCol())) {
      minEnemy = enemy;
    }
  }
  return minEnemy;
}

CCArray* EnemyManager::getFilteredEnemies(boost::function<bool (Enemy*)>filter) {
  CCArray* enemies = (CCArray*)CCArray::create();
  CCObject* obj = NULL;
  CCARRAY_FOREACH(_enemies, obj) {
    Enemy* enemy = (Enemy*)obj;
    if (filter(enemy)) {
      enemies->addObject(enemy);
    }
  }
  return enemies;
}

bool EnemyManager::attackEnemy(Enemy* enemy, int damage) {
  if (_enemies->containsObject(enemy)) {
    return enemy->damage(damage);
  }
  return false;
}

CCArray* EnemyManager::performSkill(Skill* skill) {
  SkillRange range = skill->getRange();
  CCArray* targets = (CCArray*)CCArray::create();
  if (range == SkillRangeSingle) {
    Enemy* target = this->getNearestEnemy();
    if (target) {
      targets->addObject(target);
    }
  }
  CCObject* obj = NULL;
  CCARRAY_FOREACH(targets, obj) {
    Enemy* target = (Enemy*)obj;
    if (target->damage(skill->getAttack())) {
      this->removeEnemy(target);
    }
  }
  return targets;
}
