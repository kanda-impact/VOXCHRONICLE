//
//  Controller.h
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/8.
//
//

#ifndef __VOXCHRONICLE__Controller__
#define __VOXCHRONICLE__Controller__

#include <iostream>
#include "cocos2d.h"
#include "Skill.h"

using namespace cocos2d;

class Controller : public CCLayer {
 private:
  CCArray* _triggers;
  virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
  virtual void registerWithTouchDispatcher();

public:
  virtual bool init();
  ~Controller();
  Controller();
  void resetAllTriggers();
  int currentTriggerIndex();
  Skill* currentTriggerSkill();
  void setSkills(CCArray* skills);
  LAYER_CREATE_FUNC(Controller)
};

#endif /* defined(__VOXCHRONICLE__Controller__) */
