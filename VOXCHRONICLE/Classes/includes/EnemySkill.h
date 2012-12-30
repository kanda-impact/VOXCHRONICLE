//
//  EnemySkill.h
//  VOXCHRONICLE
//
//  Created by giginet on 2012/12/31.
//
//

#ifndef __VOXCHRONICLE__EnemySkill__
#define __VOXCHRONICLE__EnemySkill__

#include <iostream>
#include "cocos2d.h"
#include "Enemy.h"
#include "CharacterManager.h"
#include "EnemyManager.h"
#include "LuaObject.h"

using namespace cocos2d;

class EnemySkill :public CCObject {
 private:
  string _name;
  LuaObject* _lua;
 public:
  EnemySkill(const char* identifier);
  ~EnemySkill();
  void performSkill(Enemy* user, CharacterManager* characterManager, EnemyManager* enemyManager);
};

#endif /* defined(__VOXCHRONICLE__EnemySkill__) */
