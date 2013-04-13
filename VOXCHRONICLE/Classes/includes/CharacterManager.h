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
#include <queue>

#include "Character.h"
#include "Skill.h"
#include "MusicSet.h"

// ダメージタイプ
typedef enum {
  DamageTypeNone, // デフォルト
  DamageTypeHit, // 通常攻撃命中
  DamageTypeNoDamage, // 元々威力のない攻撃命中
  DamageTypeDisable,  // 無効化された敵に攻撃
  DamageTypeShield, // 盾による無効化
  DamageTypeInvincible, // 無敵による無効化
  DamageTypeWeak, // 弱点
  DamageTypePhysicalResist, // 物理攻撃耐性
  DamageTypeMagicalResist, // 魔法攻撃耐性
  DamageTypePhysicalInvalid, // 物理攻撃無効
  DamageTypeMagicalInvalid, // 魔法攻撃無効
  DamageTypeShieldBreak, // 盾破壊
  DamageTypeBarrierBreak, // バリアー破壊
  DamageTypeDeath, // 死亡
  DamageTypeAbsorption // ダメージ吸収
} DamageType;

typedef struct {
  int damage;
  DamageType damageType;
} DamageInfo;

class CharacterManager :public CCObject {
 private:
  int _maxHP;
  int _maxMP;
  int _hp;
  int _mp;
  int _exp;
  int _drumLevel;
  int _repeatCount;
  int _repeatCountRaw;
  int _waitTurn;
  int _tension;
  int _levelCache;
  bool _shield;
  bool _isExpDirty;
  std::queue<DamageInfo>* _damageInfoQueue;
  Character* _currentCharacter;
  CCArray* _characters;
  Skill* _lastSkill;
  Skill* _currentSkill;
  int executeLuaFunction(const char* methodName, int argument);
  int getLevel(int exp);
  int getCurrentCharacterIndex();
  
 public:
  CharacterManager();
  ~CharacterManager();
  
  /**
   現在のターン、スキルを実行中かどうか返します
   前作の溜め攻撃のような2ターン以上かかる技向けのメソッドですが
   現行では、レベルデザイン的に廃止になったのでオワコン
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
  
  // getter
  // getterです。意味は察してください
  Character* getCurrentCharacter();
  int getTension();
  bool getShield();
  Skill* getCurrentSkill();
  Skill* getLastSkill();
  int getHP();
  int getMP();
  int getExp();
  int getMaxHP();
  int getMaxMP();
  int getDrumLevel();
  int getWaitTurn();
  int getRepeatCount();
  int getRepeatCountRaw();
  CCArray* getCharacters();
  std::queue<DamageInfo>* getDamageInfoQueue();
  
  // setter
  void setExp(int exp);
  void setLastSkill(Skill* skill);
  void setCurrentSkill(Skill* skill);
  void setShield(bool s);
  void setLevel(int l);
  void setDrumLevel(int l);
  void setWaitTurn(int waitTurn);
  void setRepeatCount(int repeatCount);
  void setRepeatCountRaw(int repeatCount);
};

#endif /* defined(__VOXCHRONICLE__CharacterManager__) */
