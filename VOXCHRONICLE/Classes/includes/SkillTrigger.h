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

using namespace cocos2d;

/**
 コントローラー上に配置されるボタンクラスです
*/
class SkillTrigger : public CCSprite, CCTouchDelegate {
 private:
  bool _press;
  bool _enable;
  Skill* _skill;
  
 public:
  static SkillTrigger* create(const char* filename);
  bool getPress();
  void setPress(bool press);
  Skill* getSkill();
  void setSkill(Skill* skill);
  ~SkillTrigger();
  SkillTrigger();
  bool getEnable();
  void setEnable(bool e);
};

#endif /* defined(__VOXCHRONICLE__SkillTrigger__) */
