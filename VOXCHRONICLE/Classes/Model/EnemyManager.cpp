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
#include "LuaObject.h"

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
  _enemyPopLots = new vector<bool>();
  return true;
}

EnemyManager::EnemyManager() {
  _trash = CCArray::create();
  _trash->retain();
}

EnemyManager::~EnemyManager() {
  _trash->release();
  _enemiesQueue->release();
  delete _enemyPopLots;
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
  if (_enemyPopLots->size() == 0) {
    for (int i = 0; i < 100; ++i) {
      if (i < 100.0 * this->getLevel()->getEnemyPopRate()) {
        _enemyPopLots->push_back(true);
      } else {
        _enemyPopLots->push_back(false);
      }
    }
    random_shuffle(_enemyPopLots->begin(), _enemyPopLots->end());
  }
  bool lot = _enemyPopLots->back();
  _enemyPopLots->pop_back();
  if (lot) {
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

bool EnemyManager::performLuaFunction(Skill* skill, Enemy* target, CharacterManager* characterManager) {
  LuaObject* lua = skill->getLuaObject();
  lua_State* L = lua->getLuaEngine()->getLuaState();
  lua_getglobal(L, "Skill");
  int table = lua_gettop(L);
  lua_getfield(L, table, "performSkill");
  if (lua_isfunction(L, lua_gettop(L))) {
    if (target) {
      lua->getLuaEngine()->pushCCObject(target, "Enemy");
      target->retain();
    } else {
      lua->getLuaEngine()->pushNil();
    }
    lua->getLuaEngine()->pushCCObject(characterManager, "CharacterManager");
    characterManager->retain();
    if (lua_pcall(L, 2, 1, 0)) {
      cout << lua_tostring(L, lua_gettop(L)) << endl;
      return false;
    }
    if (target) {
      lua->getLuaEngine()->removeScriptObjectByCCObject(target);
    }
    lua->getLuaEngine()->removeScriptObjectByCCObject(characterManager);
    return true;
  }
  lua->getLuaEngine()->cleanStack();
  return false;
}

CCDictionary* EnemyManager::performSkill(Skill* skill, CharacterManager* characterManager) {
  int exp = 0;
  CCDictionary* info = CCDictionary::create();
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
    if (this->getChildrenCount() > 0) {
      targets->addObjectsFromArray(this->getChildren());
    }
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
  if (skill->getRange() == SkillRangeSelf) {
    this->performLuaFunction(skill, NULL, characterManager);
  } else {
    CCObject* obj = NULL;
    CCARRAY_FOREACH(targets, obj) {
      Enemy* target = (Enemy*)obj;
      if (!performLuaFunction(skill, target, characterManager)) {
        target->damage(characterManager->calcDamage(target, skill));
      }
      if (target->getHP() <= 0) {
        exp += target->getExp();
        _trash->addObject(target);
        this->removeEnemy(target);
      }
    }
  }
  
  // テンション使ってないときreset
  if (strcmp(skill->getSlug(), "tension")) {
    characterManager->resetTension();
  }
  info->setObject(targets, "enemies");
  info->setObject(CCInteger::create(exp), "exp");
  characterManager->addExp(exp);
  return info;
}

Level* EnemyManager::getLevel() {
  return _level;
}

void EnemyManager::setLevel(Level *lv) {
  float preEnemyPopRate = 0;
  if (_level) {
    _level->release();
    preEnemyPopRate = _level->getEnemyPopRate();
  }
  if (lv) {
    lv->retain();
  }
  _level = lv;
  // モンスター出現率が変化していたら、クジをリセットする
  if (preEnemyPopRate != _level->getEnemyPopRate()) {
    _enemyPopLots->clear();
  }
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

void EnemyManager::draw() {
  // とりあえずVOX1を移植
  // 面倒なので他の人に計算してもらう
  CCLayer::draw();
  CCDirector* director = CCDirector::sharedDirector();
  float sum = (1 + MAX_ROW) * MAX_ROW / 2;
  for (int i = 0; i < MAX_ROW; ++i) {
    int sy = 80 + 25 * 0;
    int ey = 80 + 25 * (MAX_ROW - 1);
    float tempSum = (1 + (MAX_ROW - i)) * (MAX_ROW - i) / 2;
    float scale = 1.0 * tempSum / sum;
    float y = ey + (sy - ey) * tempSum / sum - 125 * scale;
    CCPoint origin = CCPointMake(0, y);
    CCSize size = director->getWinSize();
    CCPoint dest = CCPointMake(size.width, y);
    float opacity = 0.25 + 0.75 * ((float)(MAX_ROW - i) / MAX_ROW);
    ccDrawColor4F(1.0 * opacity, 1.0 * opacity, 1.0 * opacity, 1);
    ccDrawLine(origin, dest);
  }
}

void EnemyManager::purgeAllTrash() {
  _trash->removeAllObjects();
}