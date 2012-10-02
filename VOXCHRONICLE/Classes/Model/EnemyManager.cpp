//
//  EnemyManager.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/28.
//
//

#include <boost/random.hpp>
#include <boost/lambda/lambda.hpp>

#include "EnemyManager.h"

using namespace boost;
using namespace boost::lambda;

bool EnemyManager::init() {
  if (!CCLayer::init()) {
    return false;
  }
  _enemiesQueue = CCArray::create();
  _enemiesQueue->retain();
  _level = NULL;
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
  _enemiesQueue->release();
}

Enemy* EnemyManager::popEnemy() {
  if (_enemiesQueue->count() == 0) {
    _enemiesQueue->addObjectsFromArray(this->createEnemyQueue());
  }
  Enemy* enemy = (Enemy*)_enemiesQueue->lastObject();
  _enemiesQueue->removeLastObject();
  int col = rand() % 3;
  enemy->setCol(col);
  this->addChild(enemy, (MAX_ROW - enemy->getRow()));
  return enemy;
}

Enemy* EnemyManager::lotPopEnemy() {
  _enemyCount += rand() % 100;
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
  CCARRAY_FOREACH(this->getChildren(), obj) {
    Enemy* enemy = (Enemy*)obj;
    if (enemy->getRow() == row && enemy->getCol() == col) {
      return enemy;
    }
  }
  return NULL;
}

CCArray* EnemyManager::getEnemies() {
  return this->getChildren();
}

bool EnemyManager::removeEnemy(Enemy* enemy) {
  if (this->getChildren()->containsObject(enemy)) {
    this->removeChild(enemy, true);
    return true;
  }
  return false;
}

Enemy* EnemyManager::getNearestEnemy() {
  CCObject* obj = NULL;
  Enemy* minEnemy = NULL;
  CCARRAY_FOREACH(this->getChildren(), obj) {
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
  CCARRAY_FOREACH(this->getChildren(), obj) {
    Enemy* enemy = (Enemy*)obj;
    if (filter(enemy->getRow(), enemy->getCol())) {
      enemies->addObject(enemy);
    }
  }
  return enemies;
}

bool EnemyManager::attackEnemy(Enemy* enemy, int damage) {
  if (this->getChildren()->containsObject(enemy)) {
    return enemy->damage(damage);
  }
  return false;
}

CCArray* EnemyManager::performSkill(Skill* skill, CharacterManager* characterManager) {
  
  characterManager->setShield(false);
  // ターゲットの決定
  SkillRange range = skill->getRange();
  CCArray* targets = (CCArray*)CCArray::create();
  if (range == SkillRangeSingle) {
    Enemy* target = this->getNearestEnemy();
    if (target) {
      targets->addObject(target);
    }
  } else if (range == SkillRangeAll) {
    targets->addObjectsFromArray(this->getChildren());
  } else if (range == SkillRangeHorizontal) {
    Enemy* target = this->getNearestEnemy();
    targets->addObject(target);
    boost::function<bool (int, float)> predicate = _2 == target->getRow();
    targets->addObjectsFromArray(this->getFilteredEnemies(predicate));
  } else if (range == SkillRangeVertical) {
    Enemy* target = this->getNearestEnemy();
    targets->addObject(target);
    boost::function<bool (int, float)> predicate = _1 == target->getCol();
    targets->addObjectsFromArray(this->getFilteredEnemies(predicate));
  } else if (range == SkillRangeBack) {
    // 実装途中。後で考える
    Enemy* target = this->getNearestEnemy();
    targets->addObject(target);
    boost::function<bool (int, float)> predicate = _1 == target->getCol();
    targets->addObjectsFromArray(this->getFilteredEnemies(predicate));
  }
  
  // ターゲットに技の効果を与える
  CCObject* obj = NULL;
  if (skill->getRange() == SkillRangeSelf) {
    if (!strcmp(skill->getSlug(), "tension")) {
      characterManager->chargeTension();
    } else if (!strcmp(skill->getSlug(), "change")) {
      characterManager->setCurrentCharacter((characterManager->getCurrentCharacterIndex() + 1) % 2);
    } else if (!strcmp(skill->getSlug(), "shield")) {
      characterManager->setShield(true);
    }
  } else {
    CCARRAY_FOREACH(targets, obj) {
      Enemy* target = (Enemy*)obj;
      if (!strcmp(skill->getSlug(), "knockback")) {
        target->moveRow(MAX_ROW - target->getRow() - 1);
      }
      if (target->damage(characterManager->calcDamage(target, skill))) {
        characterManager->addExp(target->getExp());
        this->removeEnemy(target);
      }
    }
  }
  
  // テンション使ってないときreset
  if (strcmp(skill->getSlug(), "tension")) {
    characterManager->resetTension();
  }
  
  return targets;
}

Level* EnemyManager::getLevel() {
  return _level;
}

void EnemyManager::setLevel(Level *lv) {
  if (_level) {
    _level->release();
  }
  if (lv) {
    lv->retain();
  }
  _level = lv;
}

CCArray* EnemyManager::createEnemyQueue() {
  CCArray* queue = CCArray::create();
  list< pair<string, int> > table = _level->getEnemyTable();
  for (list< pair<string, int> >::iterator it = table.begin(); it != table.end(); ++it ) {
    string enemyName = it->first;
    int count = it->second;
    for (int i = 0; i < count; ++i) {
      Enemy* enemy = Enemy::create(enemyName.c_str());
      queue->addObject(enemy);
    }
  }
  int size = queue->count();
  for (int i = 0; i < size; ++i) {
    queue->exchangeObjectAtIndex(i, rand() % size);
  }
  return queue;
}