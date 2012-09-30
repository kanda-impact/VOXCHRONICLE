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

// ダメージタイプ
typedef enum {
  DamageTypeHit,
  DamageTypeShield,
  DamageTypeInvisible,
  DamageTypeWeak,
  DamageTypeDeath,
  DamageTypeAbsorption
} DamageType;

class CharacterManager :public CCObject {
 private:
  int _hp;
  int _mp;
  int _exp;
  Character* _currentCharacter;
  CCArray* _characters;
  Skill* _lastSkill;
  Skill* _currentSkill;
  int _repeatCount;
  int _waitTurn;
  int _tension;
  bool _shield;
 public:
  CharacterManager();
  ~CharacterManager();
  const char* performSkill(Skill* skill);
  bool isPerforming();
  void chargeTension();
  void resetTension();
  int calcDamage(Enemy* enemy, Skill* skill);
  void addExp(int exp);
  int getLevel(int exp);
  int getCurrentCharacterIndex();
  DamageType damage(Enemy* attacker, int damage);
  
  // getter
  Character* getCurrentCharacter();
  int getTension();
  bool getShield();
  int getHP();
  int getMP();
  
  // setter
  void setLastSkill(Skill* skill);
  void setCurrentSkill(Skill* skill);
  void setCurrentCharacter(int idx);
  void setShield(bool s);
  
};

#endif /* defined(__VOXCHRONICLE__CharacterManager__) */
