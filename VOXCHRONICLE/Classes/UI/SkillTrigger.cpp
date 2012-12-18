//
//  SkillTrigger.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/8.
//
//

#include <sstream>
#include "SkillTrigger.h"
#include "FileUtils.h"
#include "CCDrawingPrimitives.h"

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
  _state = SkillTriggerStateNormal;
}

SkillTrigger::~SkillTrigger() {
  _skill->release();
}

bool SkillTrigger::getPress() {
  return _press;
}

void SkillTrigger::setPress(bool press) {
  if (_state != SkillTriggerStateNormal && _state != SkillTriggerStateSelected) return;
  _press = press;
  if (press) {
    _state = SkillTriggerStateSelected;
    CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(FileUtils::getFilePath("Image/Main/UI/proto/trigger_on.png").c_str());
    this->setTexture(texture);
  } else {
    _state = SkillTriggerStateNormal;
    this->setColor(_color);
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
    ss << "Image/Main/UI/command/" << skill->getIdentifier() << "_icon.png";
    CCSprite* icon = CCSprite::create(FileUtils::getFilePath(ss.str().c_str()).c_str());
    icon->setColor(ccc3(255, 0, 0));
    icon->setPosition(CCPointMake(40, 40));
    const int iconTag = 1;
    if (this->getChildByTag(iconTag)) {
      this->removeChildByTag(iconTag, true);
    }
    this->addChild(icon, 1000, iconTag);
  }
  this->setSkillTriggerState(SkillTriggerStateNormal);
}

int SkillTrigger::getSkillTriggerState() {
  return _state;
}

void SkillTrigger::setSkillTriggerState(SkillTriggerState state) {
  _state = state;
  if (_state == SkillTriggerStateSelected) {
    this->setPress(true);
  } else {
    this->setPress(false);
  }
  float opacity = 255;
  if (_state == SkillTriggerStateUnknown || _state == SkillTriggerStateDisable) {
    opacity = 64;
  }
  this->setOpacity(opacity);
  CCSprite* icon = (CCSprite*)this->getChildByTag(1);
  if (_state == SkillTriggerStateUnknown) {
    icon->setOpacity(0);
  } else {
    icon->setOpacity(opacity);
  }
}

void SkillTrigger::setColor(SkillTriggerColor color) {
  _color = color;
  string filename;
  if (_color == SkillTriggerColorVox) {
    filename = FileUtils::getFilePath("Image/Main/UI/proto/trigger_vox.png");
  } else if (_color == SkillTriggerColorLaska) {
    filename = FileUtils::getFilePath("Image/Main/UI/proto/trigger_laska.png");
  }
  CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(filename.c_str());
  this->setTexture(texture);
  
}