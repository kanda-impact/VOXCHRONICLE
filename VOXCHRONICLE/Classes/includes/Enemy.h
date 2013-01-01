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
#include <map>

#include "cocos2d.h"

#include "Skill.h"
#include "CharacterManager.h"

using namespace std;
using namespace cocos2d;

typedef enum {
  EnemyItemNone,
  EnemyItemShield,
  EnemyItemBarrier
} EnemyItem;

class EnemyManager;

class Enemy : public CCSprite {
 private:
  string* _name;
  int _hp;
  int _maxHP;
  int _mp;
  int _exp;
  int _attack;
  int _row;
  int _col;
  int _speed;
  int _speedCount;
  int _counter;
  int _level;
  int _frameCount;
  int _minRow;
  bool _hasFrame;
  const char* _imageName;
  SkillType _type;
  EnemyItem _item;
  void update(float dt);
  void setLifeColor();
  LuaObject* _lua;
  string _scriptPath;
  std::map<string, int>* _register;
 public:
  static Enemy* create(const char* enemyName);
  Enemy();
  ~Enemy();
  void setRow(float r);
  void setCol(int c);
  float bottomLine();
  void moveRow(float r);
  Enemy* initWithScriptName(const char* scriptName);
  void setRowAndCol(int row, float col);
  bool canMove();
  CCSprite* createFrameSprite();
  
  /**
   使用したSkillとCharacterManagerを与えてダメージを与えます。
   ダメージの状態をDamageTypeとして返します
   @param Skill* 使用したスキルを渡します
   @param CharacterManager* CharacterManagerを渡します
   @return ダメージを与えた結果をダメージタイプとして返却します
   */
  DamageType damage(Skill* skill, CharacterManager* characterManager);
  
  /**
   Luaに定義された敵の技を使う関数を実行します
   技が発動した場合はtrue、しなかった場合はfalseを返します
   @params CharacterManager* CharacterManagerを渡します
   @params EnemyManager* EnemyManagerを渡します
   @return bool 技を使ったかどうかを返します
   */
  bool performSkill(CharacterManager* characterManager, EnemyManager* enemyManager);
  
  
  /**
   敵キャラのレジスタの値を取り出します
   主にスクリプト側から数ターンに跨ぐ行動のステートを保存したりするのに使います
   未登録の値を取り出そうとした場合は、第二引数を強制的に返します
   @param const char* key 取り出す値のキー
   @param int defaultValue キーが未登録だったときに返却する値
   @return int 登録されている値
   */
  int getRegister(const char* key, int defaultValue);
  
  /**
   敵キャラのレジスタの値を登録します
   主にスクリプト側から利用します
   @param const char* key
   @param int value 登録する値
   */
  void setRegister(const char* key, int value);
  
  /**
   あるキーを与えたとき、そのレジスタに登録済みかどうかを返します
   @param const char* key キー
   @return bool 登録済みかどうか
   */
  bool hasRegister(const char* key);
  
  int getHP();
  float getRow();
  int getCol();
  int getLevel();
  int getAttack();
  float getCurrentScale(float row);
  int getExp();
  int getCounter();
  SkillType getType();
  EnemyItem getItem();
  
  void setItem(EnemyItem item);
};

#endif /* defined(__VOXCHRONICLE__Enemy__) */
