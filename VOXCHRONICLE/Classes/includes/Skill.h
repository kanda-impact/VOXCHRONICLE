//
//  Skill.h
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/29.
//
//

#ifndef __VOXCHRONICLE__Skill__
#define __VOXCHRONICLE__Skill__

#include <iostream>
#include "cocos2d.h"
#include "LuaObject.h"

using namespace cocos2d;

typedef enum {
  SkillTypeNone = 0,
  SkillTypeNormal = 1,   // 無属性
  SkillTypePhysical = 2, // 物理属性
  SkillTypeMagical = 3   // 魔法属性
} SkillType;

typedef enum {
  SkillRangeSingle = 0,     // 単体攻撃
  SkillRangeAll = 1,        // 全体攻撃
  SkillRangeHorizontal = 2, // 横攻撃
  SkillRangeVertical = 3,   // 縦攻撃
  SkillRangeBack = 4,       // 一番奥の敵攻撃
  SkillRangeSelf = 5,       // 自分が対象
  SkillRangeFront = 6,      // 最前列の敵全てが対象
} SkillRange;

typedef enum {
  SkillPerformTypeNone,
  SkillPerformTypeSuccess, // スキル成功
  SkillPerformTypeCharge, // スキルチャージ中
  SkillPerformTypeFailure // スキル失敗
} SkillPerformType;

typedef enum {
  SkillEffectTypeNone,   // エフェクトを表示させません
  SkillEffectTypeTarget, // 対象の敵1体にのみ表示させます
  SkillEffectTypeAll     // 画面全体に表示させます
} SkillEffectType;

class Skill :public CCObject {
 private:
  int _acquirementLV;
  int _maxRepeat;
  int _turn;
  int _mp;
  int _effectFrames;
  int _tensionLevel;
  bool _common;
  bool _se;
  bool _loop;
  string _name;
  string _identifier;
  SkillRange _range;
  SkillType _type;
  LuaObject* _lua;
  CCArray* _messages;
  int _cutinType;
 public:
  Skill(const char* identifier);
  ~Skill();
  string getName();
  string getIdentifier();
  int getTurn();
  int getPower(CCObject* characterManager);
  int getMaxRepeat();
  int getMP();
  int getAcquirementLV();
  int getCutinType();
  void setAcquirementLV(int lv);
  int getEffectFrames();
  int getTensionLevel();
  bool isCommon();
  bool hasSE();
  bool isLoop();
  SkillEffectType getEffectType();
  SkillRange getRange();
  SkillType getType();
  LuaObject* getLuaObject();
  CCArray* getMessages();
};

typedef struct {
  Skill* skill;
  string skillTrackName;
  SkillPerformType type;
} SkillPerformInfo;

#endif /* defined(__VOXCHRONICLE__Skill__) */
