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
  _enemyNamesQueue = CCArray::create();
  _enemyNamesQueue->retain();
  _level = NULL;
  mt19937 gen( static_cast<unsigned long>(time(0)) );
  uniform_smallint<> dst( 0, 2 );
  variate_generator<
  mt19937&, uniform_smallint<>
  > rand( gen, dst );
  _enemyPopLots = new vector<bool>();
  _boss = NULL;
  return true;
}

EnemyManager::EnemyManager() {
  _trash = CCArray::create();
  _trash->retain();
}

EnemyManager::~EnemyManager() {
  _trash->release();
  _enemyNamesQueue->release();
  delete _enemyPopLots;
}

Enemy* EnemyManager::popEnemy() {
  if (_enemyNamesQueue->count() == 0) {
    _enemyNamesQueue->addObjectsFromArray(this->createEnemyQueue());
  }
  if (_enemyNamesQueue->count() > 0) {
    const char* enemyName = ((CCString*)_enemyNamesQueue->lastObject())->getCString();
    Enemy* enemy = Enemy::create(enemyName);
    if (enemy != NULL) {
      _enemyNamesQueue->removeLastObject();
      int col = rand() % 3;
      enemy->setCol(col);
      this->addChild(enemy, (MAX_ROW - enemy->getRow()));
      return enemy;
    }
  }
  return NULL;
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
    _trash->addObject(enemy); // 遅延解法のため、ゴミ箱に追加してpoolさせておく
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

CCArray* EnemyManager::getFilteredEnemies(boost::function<bool (float, int)>filter) {
  CCArray* enemies = CCArray::create();
  CCObject* obj = NULL;
  CCARRAY_FOREACH(this->getChildren(), obj) {
    Enemy* enemy = (Enemy*)obj;
    if (filter((float)enemy->getRow(), (int)enemy->getCol())) {
      enemies->addObject(enemy);
    }
  }
  return enemies;
}

bool EnemyManager::performLuaFunction(Skill* skill, Enemy* target, CharacterManager* characterManager) {
  LuaObject* lua = skill->getLuaObject();
  lua_State* L = lua->getLuaEngineWithLoad()->getLuaState();
  lua_getglobal(L, "Skill");
  int table = lua_gettop(L);
  lua_getfield(L, table, "performSkill");
  if (lua_isfunction(L, lua_gettop(L))) {
    lua->pushCCObject(skill, "Skill");
    if (target) {
      lua->pushCCObject(target, "Enemy");
    } else {
      lua->getLuaEngine()->pushNil();
    }
    lua->pushCCObject(characterManager, "CharacterManager");
    lua->pushCCObject(this, "EnemyManager");
    if (lua_pcall(L, 4, 1, 0)) {
      cout << lua_tostring(L, lua_gettop(L)) << endl;
      return false;
    }
    return true;
  }
  lua->getLuaEngine()->cleanStack();
  return false;
}

CCDictionary* EnemyManager::performSkill(Skill* skill, CCArray* targets, CharacterManager* characterManager) {
  int exp = 0;
  CCDictionary* info = CCDictionary::create();
  characterManager->setShield(false);
  CCArray* damages = CCArray::create();
  CCArray* damageTypes = CCArray::create();
  if (skill->getMP() <= characterManager->getMP()) {
    // ターゲットに技の効果を与える
    if (skill->getRange() == SkillRangeSelf) {
      this->performLuaFunction(skill, NULL, characterManager);
    }
    bool nextLvExp = false; // もし、expが-1の敵が1体でもいたらtrueに
    CCObject* obj = NULL;
    CCARRAY_FOREACH(targets, obj) {
      Enemy* target = (Enemy*)obj;
      int beforeHP = target->getHP();
      // 追加効果がある場合、関数を呼び出す
      performLuaFunction(skill, target, characterManager);
      DamageType damageType = DamageTypeNone;
      if (skill->getPowerWithTension(characterManager->getTension()) != 0) {
        // 威力が1以上の場合、ダメージを与える
        damageType = target->damage(skill, characterManager, false);
      } else {
        // 威力が0の場合、NoDamageを設定する
        damageType = DamageTypeNoDamage;
      }
      int damage = beforeHP - target->getHP();
      damages->addObject(CCInteger::create(damage));
      damageTypes->addObject(CCInteger::create((int)damageType));
      if (target->getHP() <= 0) {
        if (_boss == target) {
          _boss->setAnimationClip("death", 1, true); // 敵がボスなら殺さない
          _boss->setMovable(false);
        } else {
          if (target->getExp() == -1) nextLvExp = true;
          if (nextLvExp) {
            exp = -1; // 強制的に経験値を-1にする
          } else {
            exp += target->getExp();
          }
          this->removeEnemy(target);
        }
      }
    }
    characterManager->addMP(-1 * skill->getMP());
  } else {
    cout << "MP is nothing!" << endl;
  }
  
  info->setObject(targets, "enemies");
  info->setObject(CCInteger::create(exp), "exp");
  info->setObject(damages, "damages");
  info->setObject(damageTypes, "damageTypes");
  if (exp == -1) { // 経験値が-1のとき、強制的に次のレベルになるだけの経験値を与える
    int currentLv = characterManager->getLevel();
    int requireExp = characterManager->getExpWithLevel(currentLv + 1);
    characterManager->addExp(requireExp - characterManager->getExp());
  } else {
    characterManager->addExp(exp);
  }
  return info;
}

CCArray* EnemyManager::getTargets(Skill *skill) {
  // ターゲットの決定
  CCArray* targets = CCArray::create();
  SkillRange range = skill->getRange();
  if (range == SkillRangeSingle) {
    Enemy* target = this->getNearestEnemy();
    if (target) {
      boost::function<bool (int, float)> predicate = _1 == target->getRow() && _2 == target->getCol();
      CCArray* array = this->getFilteredEnemies(predicate);
      targets->addObjectsFromArray(array);
    }
  } else if (range == SkillRangeAll) {
    if (this->getEnemies()->count() > 0) {
      targets->addObjectsFromArray(this->getEnemies());
    }
  } else if (range == SkillRangeHorizontal) {
    Enemy* target = this->getNearestEnemy();
    targets->addObject(target);
    boost::function<bool (int, float)> predicate = _1 == target->getRow();
    targets->addObjectsFromArray(this->getFilteredEnemies(predicate));
  } else if (range == SkillRangeVertical) {
    Enemy* target = this->getNearestEnemy();
    targets->addObject(target);
    boost::function<bool (int, float)> predicate = _2 == target->getCol();
    targets->addObjectsFromArray(this->getFilteredEnemies(predicate));
  } else if (range == SkillRangeBack) {
    // HPの一番高い敵を狙う
    Enemy* target = NULL;
    CCObject* obj = NULL;
    CCARRAY_FOREACH(this->getEnemies(), obj) {
      Enemy* enemy = (Enemy*)obj;
      if (target == NULL) {
        target = enemy;
      }
      if (target->getHP() < enemy->getHP()) {
        target = enemy;
      }
    }
    if (target != NULL) {
      targets->addObject(target);
    }
  } else if (range == SkillRangeFront) {
    // スラッシュ
    // 一番前の敵の後ろ4列
    Enemy* nearest = this->getNearestEnemy();
    boost::function<bool (int, float)> predicate = nearest->getRow() <= _1 && _1 <= nearest->getRow() + 4;
    targets->addObjectsFromArray(this->getFilteredEnemies(predicate));
  }
  return targets;
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
      CCString* str = CCString::create(enemyName);
      queue->addObject(str);
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
  for (int row = 0; row < MAX_ROW; ++row) {
    CCPoint line = EnemyManager::calcLinePosition(row, 1);
    CCPoint origin = ccp(0, line.y);
    CCPoint end = ccp(director->getWinSize().width, line.y);
    float opacity = 0.25 + 0.75 * ((float)(MAX_ROW - row) / MAX_ROW);
    ccDrawColor4F(1.0 * opacity, 1.0 * opacity, 1.0 * opacity, 1);
    ccDrawLine(origin, end);
  }
}

void EnemyManager::purgeAllTrash() {
  _trash->removeAllObjects();
}

void EnemyManager::pushEnemiesQueue(cocos2d::CCArray *enemies) {
  CCObject* obj = NULL;
  CCARRAY_FOREACH(enemies, obj) {
    _enemyNamesQueue->addObject(obj);
  }
}

void EnemyManager::nextTurn (CharacterManager* characterManager) {
  this->lotPopEnemy();
  CCObject* obj = NULL;
  CCARRAY_FOREACH(this->getEnemies(), obj) {
    Enemy* enemy = (Enemy*)obj;
    if (enemy == NULL) continue;
    if (enemy->getEnable() && enemy->getRow() >= 0) {
      if (!enemy->performSkill(characterManager, this)) { // 敵の技を実行する
        if (enemy->canMove()) { // 何も実行されなかったら、移動できるか調べる
          enemy->moveRow(-1); // 移動できたら1歩移動する
        }
      }
    }
  }
}

void EnemyManager::removeAllEnemiesQueue() {
  _enemyNamesQueue->removeAllObjects();
}

Enemy* EnemyManager::popEnemyAt(string enemyName, int row, int col) {
  _enemyNamesQueue->addObject(CCString::create(enemyName));
  Enemy* enemy = this->popEnemy();
  enemy->setRowAndCol(row, col);
  return enemy;
}

Enemy* EnemyManager::getBoss() {
  return _boss;
}

void EnemyManager::setBoss(Enemy* boss) {
  _boss = boss;
}

CCPoint& EnemyManager::calcLinePosition(int row, int col) {
  CCPoint root = CCPointZero;
  CCPoint end = CCPointZero;
  const int width = 480;
  const int horizonWidth = 120;
  const int horizonDistance = 122.5;
  const int marginLeft = (width - horizonWidth) / 2.0f;
  const int padding = 80;
  const float scale = horizonWidth / width;
  if (col == 0) {
    root = ccp(padding, 0);
    end = ccp(marginLeft + padding * scale, horizonDistance);
  } else if (col == 1) {
    root = ccp(width / 2.0, 0);
    end = ccp(width / 2.0, horizonDistance);
  } else if (col == 2) {
    root = ccp(width - padding, 0);
    end = ccp(marginLeft + horizonWidth - padding * scale, horizonDistance);
  }
  CCPoint sub = ccpSub(end, root);
  CCPoint p = ccpAdd(root, ccpMult(sub, row / (float)MAX_ROW));
  return p;
}