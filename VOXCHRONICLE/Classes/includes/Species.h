//
//  Species.h
//  VOXCHRONICLE
//
//  Created by giginet on 2013/2/15.
//
//

#ifndef __VOXCHRONICLE__Species__
#define __VOXCHRONICLE__Species__

#include <iostream>
#include "cocos2d.h"
#include "LuaObject.h"

using namespace std;
using namespace cocos2d;

/**
 モンスターの種族クラス
 */
class Species :public CCObject {
 private:
  string _imageName;
  string _name;
  int _attack;
  int _speed;
  int _counter;
  int _minRow;
  int _animationFrames;
  bool _hasFrame;
  LuaObject* _lua;
 public:
  Species(const char* identifier);
  ~Species();
  string getImageName();
  string getName();
  int getAttack();
  int getSpeed();
  int getCounter();
  int getMinRow();
  int getAnimationFrames();
  bool hasFrame();
  string choiceEnemySkill();
};

#endif /* defined(__VOXCHRONICLE__Species__) */
