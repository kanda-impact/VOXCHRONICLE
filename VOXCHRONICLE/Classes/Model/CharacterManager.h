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
  int _maxHP;
  int _maxMP;
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
  
  int _levelCache;
  bool _isExpDirty;
  int executeExpLua(const char* methodName, int argument);
  int getLevel(int exp);
  int getCurrentCharacterIndex();
  
 public:
  CharacterManager();
  ~CharacterManager();
  const char* checkSkillTrackName(Skill* skill, bool& performed);
  bool isPerforming();
  void addTension(int t);
  void resetTension();
  int calcDamage(Enemy* enemy, Skill* skill);
  void addExp(int exp);
  DamageType damage(Enemy* attacker, int damage);
  void changeCharacter();
  void useMP(int mp);
  
  // getter
  Character* getCurrentCharacter();
  int getTension();
  bool getShield();
  Skill* getCurrentSkill();
  int getHP();
  int getMP();
  int getLevel();
  int getExpWithLevel(int level);
  int getExp();
  
  // setter
  void setLastSkill(Skill* skill);
  void setCurrentSkill(Skill* skill);
  void setShield(bool s);
  void setLevel(int l);
  
};

#endif /* defined(__VOXCHRONICLE__CharacterManager__) */
