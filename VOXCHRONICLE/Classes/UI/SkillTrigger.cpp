//
//  SkillTrigger.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/8.
//
//

#include "SkillTrigger.h"

SkillTrigger* SkillTrigger::create(const char *pszFileName) {
  SkillTrigger *pobSprite = new SkillTrigger();
  if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
    pobSprite->autorelease();
    return pobSprite;
    }
  CC_SAFE_DELETE(pobSprite);
  return NULL;
}

SkillTrigger::SkillTrigger() : CCSprite() {
}

SkillTrigger::~SkillTrigger() {
}