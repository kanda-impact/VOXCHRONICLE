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
#include "CCSprite.h"

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
  int _counter;
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
  
  /**
   ダメージを与えます。死亡時にはtrueを返します
   */
  bool damage(int d);
  
  int getExp();
  int getCounter();
};

#endif /* defined(__VOXCHRONICLE__Enemy__) */
