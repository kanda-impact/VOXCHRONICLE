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
  SkillTriggerStateNormal,    // 使用可能な状態です
  SkillTriggerStateSelected,  // 選択状態です
  SkillTriggerStateDisable,   // テンションレベルが足りなかったり、封印されていて使用できない状態です
  SkillTriggerStateUnknown    // 習得前の状態です
} SkillTriggerState;

typedef enum {
  SkillTriggerColorVox,       // オクス用ボタンカラー（青）
  SkillTriggerColorLaska      // ラスカ用ボタンカラー（赤）
} SkillTriggerColor;

using namespace cocos2d;

/**
 コントローラー上に配置されるボタンクラスです
*/
class SkillTrigger : public CCSprite, CCTouchDelegate {
 private:
  bool _press; // 押されているかどうかです
  Skill* _skill; // このトリガーが保持しているSkillです
  SkillTriggerState _state; // 現在のトリガーの状態です
  SkillTriggerColor _color; // 現在のトリガーの色です
  
 public:
  static SkillTrigger* create(const char* filename);
  bool getPress();
  void setPress(bool press);
  Skill* getSkill();
  void setSkill(Skill* skill);
  ~SkillTrigger();
  SkillTrigger();
  int getSkillTriggerState();
  void setSkillTriggerState(SkillTriggerState state);
  void setColor(SkillTriggerColor color);
};

#endif /* defined(__VOXCHRONICLE__SkillTrigger__) */
