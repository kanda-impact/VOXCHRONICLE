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
#include "macros.h"

const int iconTag = 1;

SkillTrigger::SkillTrigger(const char* skinPrefix) : CCNode() {
  _press = false;
  _skill = NULL;
  _state = SkillTriggerStateNormal;
  _skinPrefix = skinPrefix;
  _background = CCSprite::createWithSpriteFrameName(this->buildFilePath("trigger_on.png").c_str());
  _background->retain();
  _defaultScale = 1.0f;
  _currentOpacity = 255;
  this->setColor(SkillTriggerColorVox);
  this->addChild(_background);
}

SkillTrigger::~SkillTrigger() {
  _skill->release();
  _background->release();
}

string SkillTrigger::buildFilePath(const char *file) {
  string path = _skinPrefix + string("_") + string(file);
  return path.c_str();
}

bool SkillTrigger::getPress() {
  return _press;
}

void SkillTrigger::setPress(bool press) {
  if (_state != SkillTriggerStateNormal && _state != SkillTriggerStateSelected) return;
  _press = press;
  if (press) {
    _state = SkillTriggerStateSelected;
    CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(this->buildFilePath("trigger_on.png").c_str());
    _background->setTexture(frame->getTexture());
    _background->setTextureRect(frame->getRect());
    CCSprite* icon = (CCSprite*)this->getChildByTag(iconTag);
    icon->setColor(ccc3(44, 44, 44));
    this->setScale(1.2f);
  } else {
    _state = SkillTriggerStateNormal;
    this->setColor(_color);
    this->setScale(1.0f);
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
    ss << "Image/" + skill->getIdentifier() << "_icon.png";
    CCSprite* icon = (CCSprite*)this->getChildByTag(iconTag);
    if (icon) {
      this->removeChild(icon, true);
    }
    icon = CCSprite::create(FileUtils::getFilePath(ss.str().c_str()).c_str());
    this->setIcon(icon);
    icon->setScale(0.5f);
    
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
  _currentOpacity = 255;
  if (_state == SkillTriggerStateUnknown) {
    _currentOpacity = 64;
  } else if (_state == SkillTriggerStateDisable) {
    _currentOpacity = 120;
  }
  _background->setOpacity(_currentOpacity);
  CCSprite* icon = (CCSprite*)this->getChildByTag(iconTag);
  if (_state == SkillTriggerStateUnknown) {
    icon->setOpacity(0);
  } else {
    icon->setOpacity(_currentOpacity);
  }
}

void SkillTrigger::setColor(SkillTriggerColor color) {
  _color = color;
  string filename;
  CCSprite* icon = (CCSprite*)this->getChildByTag(iconTag);
  if (icon == NULL) return;
  if (_color == SkillTriggerColorVox) {
    filename = this->buildFilePath("trigger_vox.png").c_str();
    icon->setColor(ccc3(189, 217, 252));
  } else if (_color == SkillTriggerColorLaska) {
    filename = this->buildFilePath("trigger_lsk.png").c_str();
    icon->setColor(ccc3(255, 232, 202));
  }
  CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename.c_str());
  _background->setTexture(frame->getTexture());
  _background->setTextureRect(frame->getRect());
}

CCSprite* SkillTrigger::getBackground() {
  return _background;
}

void SkillTrigger::setSkinPrefix(const char *prefix) {
  _skinPrefix = prefix;
}

void SkillTrigger::runBlinkAction(float duration) {
  const int times = 3;
  float d = duration / times;
  _background->runAction(CCSequence::create(CCTintTo::create(0.1, 255, 0, 255),
                                            CCRepeat::create(CCSequence::create(CCFadeTo::create(d, 128),
                                                                                CCFadeTo::create(d, 255),
                                                                                NULL), times),
                                            CCCallFuncN::create(this, callfuncN_selector(SkillTrigger::setOpacityDelay)),
                                            CCTintTo::create(0.1, 255, 255, 255),
                                            NULL));
}

void SkillTrigger::setOpacityDelay(cocos2d::CCNode *node) {
  CCSprite* sp = (CCSprite*)node;
  sp->setOpacity(_currentOpacity);
}

void SkillTrigger::setIcon(cocos2d::CCSprite *icon) {
  if (this->getChildByTag(iconTag)) {
    this->removeChildByTag(iconTag, true);
  }
  this->addChild(icon, 0, iconTag);
}