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

class Skill :public CCObject {
 private:
  int _acquirementLV;
  int _maxRepeat;
  int _turn;
  int _power;
  int _mp;
  int _tensionLevel;
  bool _common;
  std::string* _name;
  const char* _identifier;
  SkillRange _range;
  SkillType _type;
  LuaObject* _lua;
 public:
  Skill(const char* identifier);
  ~Skill();
  const char* getName();
  const char* getIdentifier();
  int getTurn();
  int getPower();
  int getPowerWithTension(int tension);
  int getMaxRepeat();
  int getMP();
  int getAcquirementLV();
  void setAcquirementLV(int lv);
  int getTensionLevel();
  bool isCommon();
  SkillRange getRange();
  SkillType getType();
  LuaObject* getLuaObject();
};

#endif /* defined(__VOXCHRONICLE__Skill__) */
