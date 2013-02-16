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
#include "Species.h"

using namespace std;
using namespace cocos2d;

class EnemyManager;

class Enemy : public CCSprite {
private:
  int _hp;
  int _maxHP;
  int _mp;
  int _row;
  int _col;
  int _speedCount;
  int _level;
  bool _enable;
  bool _movable;
  Species* _species;
  SkillType _type;
  EnemyItem _item;
  void update(float dt);
  void setLifeColor();
  LuaObject* _lua;
  string _scriptPath;
  std::map<string, int>* _register;
  bool setAnimationAndFrame(const char* filePrefix, int frames, bool hasFrame);
  CCSprite* createFrameSprite(const char* filePrefix, int frames);
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
  
  /**
   使用したSkillとCharacterManagerを与えてダメージを与えます。
   ダメージの状態をDamageTypeとして返します
   @param Skill* 使用したスキルを渡します
   @param CharacterManager* CharacterManagerを渡します
   @param bool simulate trueのとき、実際にはダメージを与えません。結果だけ返します
   @return ダメージを与えた結果をダメージタイプとして返却します
   */
  DamageType damage(Skill* skill, CharacterManager* characterManager, bool simulate);
  
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
  
  /**
   現在の表示グラと枠を変えます
   <imageName>_<clipName>0.pngを利用します
   @param const char* imageName クリップ名
   @param int frames アニメーションフレーム数
   @param bool hasFrame 枠を持っているかどうか
   @return bool 成功したかどうか
   */
  bool setAnimationClip(const char* clipName, int frames, bool hasFrame);
  
  /**
   デフォルトのアニメーションクリップに変更します
   @return bool 成功したかどうか
   */
  bool setDefaultAnimationClip();
  
  void toggleBlink(bool toggle);
  
  int getHP();
  float getRow();
  int getCol();
  int getLevel();
  int getAttack();
  float getCurrentScale(float row);
  int getExp();
  int getCounter();
  bool getEnable();
  string getName();
  SkillType getType();
  EnemyItem getItem();
  
  void setItem(EnemyItem item);
  void setEnable(bool enable);
  
  bool isMovable();
  void setMovable(bool m);
};

#endif /* defined(__VOXCHRONICLE__Enemy__) */
