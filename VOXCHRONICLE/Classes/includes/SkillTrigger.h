//
//  SkillTrigger.h
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/8.
//
//

#ifndef __VOXCHRONICLE__SkillTrigger__
#define __VOXCHRONICLE__SkillTrigger__

#include <iostream>
#include "cocos2d.h"
#include "Skill.h"

typedef enum {
  SkillButtonStateNormal,    // 使用可能な状態です
  SkillButtonStateSelected,  // 選択状態です
  SkillButtonStateDisable,   // テンションレベルが足りなかったり、封印されていて使用できない状態です
  SkillButtonStateUnknown    // 習得前の状態です
} SkillButtonState;

using namespace cocos2d;

/**
 コントローラー上に配置されるボタンクラスです
*/
class SkillTrigger : public CCSprite, CCTouchDelegate {
 private:
  bool _press;
  Skill* _skill;
  SkillButtonState _state;
  
 public:
  static SkillTrigger* create(const char* filename);
  bool getPress();
  void setPress(bool press);
  Skill* getSkill();
  void setSkill(Skill* skill);
  ~SkillTrigger();
  SkillTrigger();
  int getSkillButtonState();
  void setSkillButtonState(SkillButtonState state);
};

#endif /* defined(__VOXCHRONICLE__SkillTrigger__) */
