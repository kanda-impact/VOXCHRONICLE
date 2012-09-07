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

using namespace cocos2d;

/**
 コントローラー上に配置されるボタンクラスです
*/
class SkillTrigger : public CCSprite {
 private:
  // Skill* _skill;

 public:
  static SkillTrigger* create(const char* filename);
  ~SkillTrigger();
  SkillTrigger();
};

#endif /* defined(__VOXCHRONICLE__SkillTrigger__) */
