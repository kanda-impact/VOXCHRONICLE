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

// ダメージタイプ
typedef enum {
  DamageTypeHit, // 通常攻撃命中
  DamageTypeShield, // 盾による無効化
  DamageTypeInvisible, // 無敵による無効化
  DamageTypeWeak, // 弱点
  DamageTypePhysicalTolerant, // 物理攻撃態勢
  DamageTypeMagicalTolerant, // 魔法攻撃態勢
  DamageTypeDeath, // 死亡
  DamageTypeAbsorption // ダメージ吸収
} DamageType;

typedef enum {
  SkillPerformTypeNone,
  SkillPerformTypeSuccess, // スキル成功
  SkillPerformTypeCharge, // スキルチャージ中
  SkillPerformTypeFailure // スキル失敗
} SkillPerformType;

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
  int executeLuaFunction(const char* methodName, int argument);
  int getLevel(int exp);
  int getCurrentCharacterIndex();
  
 public:
  CharacterManager();
  ~CharacterManager();
  const char* checkSkillTrackName(Skill* skill, SkillPerformType& performeType);
  bool isPerforming();
  void addTension(int t);
  void resetTension();
  void addExp(int exp);
  DamageType damage(int damage);
  void changeCharacter();
  int cureHP(int hp);
  void useMP(int mp);
  void updateParameters();
  
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
  int getMaxHP();
  int getMaxMP();
  
  /**
   レベル補正値を返します。
   character.luaのgetLevelOffsetRateを実行します
   @param int attackLevel 攻撃側のレベル
   @param int defenseLevel 防御側のレベル
   @return float レベル補正値を返します。通常、攻撃側のレベルが高いほど大きな値が得られます
   */
  float getLevelOffsetRate(int attackLevel, int defenseLevel);
  
  // setter
  void setLastSkill(Skill* skill);
  void setCurrentSkill(Skill* skill);
  void setShield(bool s);
  void setLevel(int l);
  
};

#endif /* defined(__VOXCHRONICLE__CharacterManager__) */
