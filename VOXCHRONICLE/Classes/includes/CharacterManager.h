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
  DamageTypeNone, // デフォルト
  DamageTypeHit, // 通常攻撃命中
  DamageTypeShield, // 盾による無効化
  DamageTypeInvisible, // 無敵による無効化
  DamageTypeWeak, // 弱点
  DamageTypePhysicalResist, // 物理攻撃耐性
  DamageTypeMagicalResist, // 魔法攻撃耐性
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
  int _drumLevel;
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
  
  /**
   現在の状況から、次のターンに鳴らす音楽のファイル名を取得します。
   また、スキル実行状態を渡します。
   @param Skill 実行するSkillを渡します。
   @param SkillPerformType& performType SkillPerformTypeを渡します
   @return string スキルファイル名
   */
  string checkSkillTrackName(Skill* skill, SkillPerformType& performeType);
  
  /**
   現在のターン、スキルを実行中かどうか返します
   @return bool スキル実行中かどうか
   */
  bool isPerforming();
  
  /**
   テンションを加えます
   テンションが最大値4を超えたとき、4にします
   @param int t 加えるテンション
   */
  void addTension(int t);
  
  /**
   テンションを0に戻します
   */
  void resetTension();
  
  /**
   経験値を取得します
   @param int exp 獲得する経験値
   */
  void addExp(int exp);
  
  /**
   現在のキャラクタにダメージを与えます
   与えたダメージによってDamageTypeを返します
   @param int damage 与えるダメージ
   */
  DamageType damage(int damage);
  
  /**
   キャラクタを切り替えます
   */
  void changeCharacter();
  
  /**
   HPを回復します。HPが最大HPを上回ったときは最大HPにします
   @param int hp 回復するHP
   @return int 回復後のHPを返します
   */
  int addHP(int hp);
  
  /**
   MPを使用します。MPが0を下回った場合は0にします
   @param int mp 使用するMP
   @return int 回復後のMPを返します
   */
  int addMP(int mp);
  
  /**
   現在のレベルの最高HP, MPを取得し、現在HP, MPを補正します
   */
  void updateParameters();
  
  /**
   レベル補正値を返します。
   character.luaのgetLevelOffsetRateを実行します
   @param int attackLevel 攻撃側のレベル
   @param int defenseLevel 防御側のレベル
   @return float レベル補正値を返します。通常、攻撃側のレベルが高いほど大きな値が得られます
   */
  float getLevelOffsetRate(int attackLevel, int defenseLevel);
  
  
  // getter
  // getterです。意味は察してください
  Character* getCurrentCharacter();
  int getTension();
  bool getShield();
  Skill* getCurrentSkill();
  int getHP();
  int getMP();
  
  /**
   現在のレベルを経験値から計算して返します
   現在呼んだときから経験値が変化していた場合は、character.luaのgetLevelが実行され返されます
   変化していなかったときは、前回実行時のレベルをキャッシュしていて、その値を返します
   @return int 現在のレベル値
   */
  int getLevel();
  
  /**
   レベルを渡すとそのレベルになるのに最低限必要な経験値を返します。
   1以下の値を渡すと0が返る気がします
   @param int level 現在のレベル値
   @return そのレベルになるのに最低限必要な経験値
   */
  int getExpWithLevel(int level);
  int getExp();
  int getMaxHP();
  int getMaxMP();
  int getDrumLevel();
  
  // setter
  void setLastSkill(Skill* skill);
  void setCurrentSkill(Skill* skill);
  void setShield(bool s);
  void setLevel(int l);
  void setDrumLevel(int l);
  
};

#endif /* defined(__VOXCHRONICLE__CharacterManager__) */
