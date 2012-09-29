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
  SkillRangeSelf = 5        // 自分が対象
} SkillRange;

class Skill :public CCObject {
 private:
  int _maxRepeat;
  int _turn;
  int _power;
  int _mp;
  bool _common;
  const char* _name;
  const char* _slug;
  SkillRange _range;
  SkillType _type;
 public:
  Skill(const char* slug);
  ~Skill();
  const char* getName();
  const char* getSlug();
  int getTurn();
  int getPower();
  int getMaxRepeat();
  int getMP();
  bool isCommon();
  SkillRange getRange();
  SkillType getType();
};

#endif /* defined(__VOXCHRONICLE__Skill__) */
