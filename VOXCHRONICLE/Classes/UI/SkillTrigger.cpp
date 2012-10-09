//
//  SkillTrigger.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/8.
//
//

#include <sstream>
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
  _press = false;
  _skill = NULL;
  _enable = true;
}

SkillTrigger::~SkillTrigger() {
  _skill->release();
}

bool SkillTrigger::getPress() {
  return _press;
}

void SkillTrigger::setPress(bool press) {
  if (!_enable) return;
  _press = press;
  if (press) {
    CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("trigger_bg_selected.png");
    this->setTexture(texture);
  } else {
    CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("trigger_bg.png");
    this->setTexture(texture);
  }
}

Skill* SkillTrigger::getSkill() {
  return _skill;
}

void SkillTrigger::setSkill(Skill* skill) {
  if (_skill) {
    _skill->release();
  }
  if (skill) {
    skill->retain();
  }
  _skill = skill;
  if (_skill) {
    std::stringstream ss;
    ss << skill->getSlug() << "_icon.png";
    CCSprite* icon = CCSprite::create(ss.str().c_str());
    icon->setColor(ccc3(255, 0, 0));
    icon->setPosition(CCPointMake(40, 40));
    const int iconTag = 1;
    if (this->getChildByTag(iconTag)) {
      this->removeChildByTag(iconTag, true);
    }
    this->addChild(icon, 1000, iconTag);
  }
  this->setEnable(true);
}

bool SkillTrigger::getEnable() {
  return _enable;
}

void SkillTrigger::setEnable(bool e) {
  _enable = e;
  float opacity = 255;
  if (!_enable) {
    opacity = 64;
  }
  this->setOpacity(opacity);
  CCSprite* icon = (CCSprite*)this->getChildByTag(1);
  icon->setOpacity(opacity);
}