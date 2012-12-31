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
#include "Skill.h"
#include "cocos2d.h"
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
 public:
  static Enemy* create(const char* enemyName);
  Enemy();
  ~Enemy();
  void setRow(float r);
  void setCol(int c);
  float bottomLine();
  void moveRow(float r);
  Enemy* initWithScriptName(const char* scriptName);
  void setColAndRow(int col, float row);
  bool canMove();
  CCSprite* createFrameSprite();
  
  /**
   使用したSkillとCharacterManagerを与えてダメージを与えます。
   ダメージの状態をDamageTypeとして返します
   */
  DamageType damage(Skill* skill, CharacterManager* characterManager);
  
  /**
   Luaに定義された敵の技を使う関数を実行します
   技が発動した場合はtrue、しなかった場合はfalseを返します
   */
  bool performSkill(CharacterManager* characterManager, EnemyManager* enemyManager);
  
  
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
