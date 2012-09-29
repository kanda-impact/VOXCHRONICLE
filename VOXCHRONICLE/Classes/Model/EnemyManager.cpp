//
//  EnemyManager.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/28.
//
//

#include <boost/random.hpp>

#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/if.hpp>
#include <boost/lambda/loops.hpp>
#include <boost/lambda/switch.hpp>
#include <boost/lambda/construct.hpp>
#include <boost/lambda/casts.hpp>
#include <boost/lambda/exceptions.hpp>
#include <boost/lambda/algorithm.hpp>

#include "EnemyManager.h"

using namespace boost;
using namespace boost::lambda;

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

CCArray* EnemyManager::getFilteredEnemies(boost::function<bool (int, float)>filter) {
  CCArray* enemies = (CCArray*)CCArray::create();
  CCObject* obj = NULL;
  CCARRAY_FOREACH(_enemies, obj) {
    Enemy* enemy = (Enemy*)obj;
    if (filter(enemy->getRow(), enemy->getCol())) {
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
  } else if (range == SkillRangeAll) {
    targets->addObjectsFromArray(_enemies);
  } else if (range == SkillRangeHorizontal) {
    Enemy* target = this->getNearestEnemy();
    boost::function<bool (int, float)> predicate = _2 == target->getRow();
    targets->addObjectsFromArray(this->getFilteredEnemies(predicate));
  } else if (range == SkillRangeVertical) {
    Enemy* target = this->getNearestEnemy();
    boost::function<bool (int, float)> predicate = _1 == target->getCol();
    targets->addObjectsFromArray(this->getFilteredEnemies(predicate));
  }
  CCObject* obj = NULL;
  CCARRAY_FOREACH(targets, obj) {
    Enemy* target = (Enemy*)obj;
    if (!strcmp(skill->getSlug(), "knockback")) {
      target->moveRow(MAX_ROW - target->getRow() - 1);
    }
    if (target->damage(skill->getPower())) {
      this->removeEnemy(target);
    }
  }
  return targets;
}
