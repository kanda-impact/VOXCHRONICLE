//
//  CharacterManager.h
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/28.
//
//

#ifndef __VOXCHRONICLE__CharacterManager__
#define __VOXCHRONICLE__CharacterManager__

#include <iostream>
#include "Character.h"
#include "Skill.h"
#include "Enemy.h"

class CharacterManager :public CCObject {
 private:
  int _hp;
  int _mp;
  Character* _currentCharacter;
  CCArray* _characters;
  Skill* _lastSkill;
  Skill* _currentSkill;
  int _repeatCount;
  int _waitTurn;
  int _tension;
 public:
  CharacterManager();
  ~CharacterManager();
  Character* getCurrentCharacter();
  const char* performSkill(Skill* skill);
  bool isPerforming();
  void setLastSkill(Skill* skill);
  void setCurrentSkill(Skill* skill);
  int getTension();
  void chargeTension();
  void resetTension();
  int calcDamage(Enemy* enemy, Skill* skill);
};

#endif /* defined(__VOXCHRONICLE__CharacterManager__) */
