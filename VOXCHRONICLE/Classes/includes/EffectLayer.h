//
//  EffectLayer.h
//  VOXCHRONICLE
//
//  Created by giginet on 2013/2/27.
//
//

#ifndef __VOXCHRONICLE__EffectLayer__
#define __VOXCHRONICLE__EffectLayer__

#include <iostream>
#include "cocos2d.h"
#include "Skill.h"
#include "EnemyManager.h"

using namespace cocos2d;

class EffectLayer :public CCLayer {
 private:
 public:
  EffectLayer();
  ~EffectLayer();
  void addSkillEffect(Skill* skill, CCArray* targets);
  void addTutorialWindow();
  void addCutin(Skill* skill);
};

#endif /* defined(__VOXCHRONICLE__EffectLayer__) */
