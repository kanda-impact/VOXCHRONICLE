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
  _background = CCSprite::create(this->buildFilePath("trigger_on.png").c_str());
  _background->retain();
  _icon = NULL;
  _defaultScale = 1.0f;
  _currentOpacity = 255;
  this->setColor(SkillTriggerColorVox);
  this->addChild(_background);
}

SkillTrigger::~SkillTrigger() {
  _skill->release();
  if (_icon != NULL) _icon->release();
  _background->release();
}

string SkillTrigger::buildFilePath(const char *file) {
  string path = string("Image/") + _skinPrefix + string("_") + string(file);
  return FileUtils::getFilePath(path.c_str());
}

bool SkillTrigger::getPress() {
  return _press;
}

void SkillTrigger::setPress(bool press) {
  if (_state != SkillTriggerStateNormal && _state != SkillTriggerStateSelected) return;
  _press = press;
  if (press) {
    _state = SkillTriggerStateSelected;
    CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(this->buildFilePath("trigger_on.png").c_str());
    _background->setTexture(texture);
    _icon->setColor(ccc3(44, 44, 44));
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
    ss << "Images/" + skill->getIdentifier() << "_icon.png";
    if (_icon != NULL) {
      _icon->getParent()->removeChild(_icon, true);
    }
    _icon = CCSprite::create(FileUtils::getFilePath(ss.str().c_str()).c_str());
    _icon->retain();
    this->addChild(_icon);
    _icon->setScale(0.25f);
    
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
  if (_state == SkillTriggerStateUnknown || _state == SkillTriggerStateDisable) {
    _currentOpacity = 64;
  }
  _background->setOpacity(_currentOpacity);
  if (_state == SkillTriggerStateUnknown) {
    _icon->setOpacity(0);
  } else {
    _icon->setOpacity(_currentOpacity);
  }
}

void SkillTrigger::setColor(SkillTriggerColor color) {
  _color = color;
  string filename;
  if (_icon == NULL) return;
  if (_color == SkillTriggerColorVox) {
    filename = this->buildFilePath("trigger_vox.png").c_str();
    _icon->setColor(ccc3(189, 217, 252));
  } else if (_color == SkillTriggerColorLaska) {
    filename = this->buildFilePath("trigger_lsk.png").c_str();
    _icon->setColor(ccc3(255, 232, 202));
  }
  CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(filename.c_str());
  _background->setTexture(texture);
  
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