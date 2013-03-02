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
#include "Skill.h"
#include "LuaObject.h"
#include "CharacterManager.h"

using namespace std;
using namespace cocos2d;

typedef enum {
  EnemyItemNone,
  EnemyItemShield,
  EnemyItemBarrier
} EnemyItem;

/**
 モンスターの種族クラス
 */
class Species :public CCObject {
 private:
  string _imageName;
  string _name;
  int _attack;
  int _counter;
  int _animationFrames;
  int _baseExp;
  bool _hasFrame;
  LuaObject* _lua;
  CCLuaValueArray* _disableSkills;
 public:
  Species(const char* identifier);
  ~Species();
  string getImageName();
  string getName();
  int getAttack();
  int getCounter();
  int getAnimationFrames();
  bool hasFrame();
  int getDefaultExp(int level, int maxHP, EnemyItem item, SkillType type);
  string choiceEnemySkill(CCObject* enemy, CCObject* characterManager, CCObject* enemyManager);
  LuaObject* getLuaObject();
  bool isEnableSkill(Skill* skill);
};

#endif /* defined(__VOXCHRONICLE__Species__) */
