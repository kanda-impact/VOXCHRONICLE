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
  SkillTypeNormal,   // 無属性
  SkillTypePhysical, // 物理属性
  SkillTypeMagical   // 魔法属性
} SkillType;

typedef enum {
  SkillRangeSingle,     // 単体攻撃
  SkillRangeAll,        // 全体攻撃
  SkillRangeHorizontal, // 横攻撃
  SkillRangeVertical,   // 縦攻撃
  SkillRangeBack        // 一番奥の敵攻撃
} SkillRange;

class Skill :public CCObject {
 private:
  int _maxRepeat;
  int _turn;
  int _attack;
  const char* _name;
  const char* _slug;
  SkillRange _range;
  SkillType _type;
 public:
  Skill(CCDictionary* info);
  ~Skill();
};

#endif /* defined(__VOXCHRONICLE__Skill__) */
