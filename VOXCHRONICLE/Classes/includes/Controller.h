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
#include "CharacterManager.h"
#include "SkillTrigger.h"
#include "Level.h"

using namespace cocos2d;

typedef enum {
  ControllerFrameTypeNone,   // フレームなし
  ControllerFrameTypeCommon, // フレーム共有
  ControllerFrameTypeFull    // オクス、ラスカのフレーム別々
} ControllerFrameType;

class Controller : public CCLayer {
 private:
  CCArray* _triggers;
  string _skinPrefix;
  virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
  virtual void registerWithTouchDispatcher();
  bool _enable;
  ControllerFrameType _frameType;
  void setFrame(CharacterManager* manager);
public:
  ~Controller();
  Controller(const char* skinPrefix);
  void resetAllTriggers();
  int currentTriggerIndex();
  Skill* currentTriggerSkill();
  SkillTrigger* getSkillTriggerFor(Skill* skill);
  void updateSkills(CharacterManager* manager, Level* level);
  void setEnable(bool enable);
  void setFrameType(ControllerFrameType type);
  void setSkinPrefix(const char* skinPrefix);
};

#endif /* defined(__VOXCHRONICLE__Controller__) */
