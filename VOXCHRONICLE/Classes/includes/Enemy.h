//
//  Enemy.h
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/28.
//
//

#ifndef __VOXCHRONICLE__Enemy__
#define __VOXCHRONICLE__Enemy__
#define MAX_ROW 8.0

#include <iostream>
#include "Skill.h"
#include "cocos2d.h"
#include "CharacterManager.h"

using namespace std;
using namespace cocos2d;

class Enemy : public CCSprite {
 private:
  string* _name;
  int _hp;
  int _maxHP;
  int _mp;
  int _exp;
  int _power;
  int _row;
  int _col;
  int _speed;
  int _speedCount;
  int _counter;
  int _level;
  SkillType _type;
  void update(float dt);
  void setLifeColor();
 public:
  static Enemy* create(const char* enemyName);
  Enemy();
  ~Enemy();
  int getHP();
  float getRow();
  void setRow(float r);
  int getCol();
  void setCol(int c);
  float bottomLine();
  void moveRow(float r);
  Enemy* initWithScriptName(const char* scriptName);
  void setColAndRow(int col, float row);
  float getCurrentScale(float row);
  bool canMove();
  int getLevel();
  
  /**
   使用したSkillとCharacterManagerを与えてダメージを与えます。
   ダメージの状態をDamageTypeとして返します
   */
  DamageType damage(Skill* skill, CharacterManager* characterManager);
  
  int getExp();
  int getCounter();
  SkillType getType();
};

#endif /* defined(__VOXCHRONICLE__Enemy__) */