//
//  Controller.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/8.
//
//

#include "SimpleAudioEngine.h"
#include <boost/lexical_cast.hpp>

#include "Controller.h"
#include "SkillTrigger.h"
#include "FileUtils.h"
#include "LuaObject.h"
#define COMMAND_COUNT 8

typedef enum {
  ControllerZOrderFrame,
  ControllerZOrderTrigger,
  ControllerZOrderTriggerPressed
} ControllerZOrder;

using namespace cocos2d;

Controller::Controller(const char* skinPrefix) {
  _triggers = CCArray::create();
  _triggers->retain();
  _enable = true;
  _skinPrefix = string(skinPrefix);
  
  // controller.luaから配置データを読みます
  LuaObject* lua = new LuaObject(FileUtils::getFilePath("Script/controller.lua").c_str());
  lua->autorelease();
  CCLuaValueArray* xs = lua->getArray("x");
  CCLuaValueArray* ys = lua->getArray("y");
  CCLuaValueArray* scales = lua->getArray("scale");
  CCLuaValueArray* rotations = lua->getArray("rotation");
  CCLuaValueArrayIterator xsit = xs->begin();
  CCLuaValueArrayIterator ysit = ys->begin();
  CCLuaValueArrayIterator scalesit = scales->begin();
  CCLuaValueArrayIterator rotationsit = rotations->begin();
  
  for (int i = 0; i < COMMAND_COUNT; ++i) {
    string index = boost::lexical_cast<string>(i + 1);
    SkillTrigger* trigger = new SkillTrigger(_skinPrefix.c_str());
    trigger->setPosition(ccp(xsit->floatValue(), ysit->floatValue()));
    trigger->getBackground()->setRotation(rotationsit->floatValue());
    trigger->getBackground()->setScale(scalesit->floatValue());
    this->addChild(trigger, ControllerZOrderTrigger);
    _triggers->addObject(trigger);
    this->setTouchEnabled(true);
    ++xsit;
    ++ysit;
    ++scalesit;
    ++rotationsit;
  }
  
  this->setEnable(false);
  _frameType = ControllerFrameTypeNone;
}

Controller::~Controller() {
  _triggers->release();
}

void Controller::setSkinPrefix(const char* prefix) {
  _skinPrefix = string(prefix);
  CCObject* obj = NULL;
  CCARRAY_FOREACH(_triggers, obj) {
    SkillTrigger* trigger = (SkillTrigger*)obj;
    trigger->setSkinPrefix(_skinPrefix.c_str());
  }
}

void Controller::registerWithTouchDispatcher() {
  CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool Controller::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent) {
  bool isTouched = false;
  if (_enable) {
    CCObject* trigger = NULL;
    CCARRAY_FOREACH(_triggers, trigger) {
      CCPoint p = ((SkillTrigger*)trigger)->getBackground()->convertTouchToNodeSpace(pTouch);
      CCSize size = ((SkillTrigger*)trigger)->getBackground()->getContentSize();
      const CCPoint triggerCenter = ccp(size.width / 2.0f, size.height / 2.0f);
      const int triggerRadius = size.width / 2.0;
      if (((SkillTrigger*)trigger)->getSkillTriggerState() == SkillTriggerStateNormal && ccpDistance(triggerCenter, p) < triggerRadius) {
        isTouched = true;
        this->resetAllTriggers();
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/cursor.mp3").c_str());
        ((SkillTrigger*)trigger)->setPress(true);
        this->reorderChild((SkillTrigger*)trigger, ControllerZOrderTriggerPressed);
        break;
      }
    }
  }
  if (!_enable || !isTouched) {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/touch.mp3").c_str());
  }
  return true;
}

void Controller::resetAllTriggers() {
  CCObject* trigger = NULL;
  CCARRAY_FOREACH(_triggers, trigger) {
    ((SkillTrigger*)trigger)->setPress(false);
    this->reorderChild((SkillTrigger*)trigger, ControllerZOrderTrigger);
  }
}

int Controller::currentTriggerIndex() {
  int i = 0;
  CCObject* trigger = NULL;
  CCARRAY_FOREACH(_triggers, trigger) {
    if (((SkillTrigger*)trigger)->getPress() ){
      return i;
    }
    ++i;
  }
  return -1;
}

void Controller::updateSkills(CharacterManager* manager) {
  CCArray* allSkills = manager->getCurrentCharacter()->getSkills();
  int level = manager->getLevel();
  CCArray* skills = manager->getCurrentCharacter()->getSkills(level);
  for (int i = 0; i < _triggers->count(); ++i) {
    if (i >= allSkills->count()) break;
    Skill* skill = (Skill*)allSkills->objectAtIndex(i);
    SkillTrigger* trigger = (SkillTrigger*)_triggers->objectAtIndex(i);
    trigger->setSkill(skill);
    if (!skills->containsObject(skill)) {
      // 習得済みスキルに入ってないとき、未習得状態に
      trigger->setSkillTriggerState(SkillTriggerStateUnknown);
    } else if (skill->getTensionLevel() > manager->getTension()) {
      // テンションレベルが足りないとき、使用不可状態に
      trigger->setSkillTriggerState(SkillTriggerStateDisable);
    } else {
      // その他のとき、通常状態に
      trigger->setSkillTriggerState(SkillTriggerStateNormal);
    }
    // 現在のキャラに応じて色を変更します
    if (manager->getCurrentCharacter()->getCharacterType() == CharacterTypeVox) {
      trigger->setColor(SkillTriggerColorVox);
    } else {
      trigger->setColor(SkillTriggerColorLaska);
    }
  }
  this->setFrame(manager);
}

Skill* Controller::currentTriggerSkill() {
  int index = this->currentTriggerIndex();
  if (index >= 0) {
    return ((SkillTrigger*)_triggers->objectAtIndex(index))->getSkill();
  }
  return NULL;
}

void Controller::setEnable(bool enable) {
  _enable = enable;
  if (enable) {
    this->setVisible(true);
  } else {
    this->setVisible(false);
  }
}

void Controller::setFrameType(ControllerFrameType type) {
  _frameType = type;
}

void Controller::setFrame(CharacterManager *manager) {
  // 超汚いけどいいや
  // 毎ターン消してるのキモイからどうにかしたい
  const int controllerFrameTag = 0;
  const CCPoint leftFramePosition = ccp(75.5, 78);
  const CCPoint rightFramePosition = ccp(397, 75.5);
  CCNode* frame = this->getChildByTag(controllerFrameTag);
  if (frame) {
    this->removeChild(frame, true);
  }
  if (_frameType != ControllerFrameTypeNone) {
    string filepathL, filepathR;
    if (_frameType == ControllerFrameTypeCommon) {
      filepathL = string("Image/") + _skinPrefix + string("_frame_left.png");
    } else {
      if (manager->getCurrentCharacter()->getCharacterType() == CharacterTypeVox) {
        filepathL = string("Image/") + _skinPrefix + string("_frame_vox_left.png");
      } else {
        filepathL = string("Image/") + _skinPrefix + string("_frame_lsk_left.png");
      }
    }
    CCSprite* leftFrame = CCSprite::create(FileUtils::getFilePath(filepathL.c_str()).c_str());
    leftFrame->setPosition(leftFramePosition);
    
    if (_frameType == ControllerFrameTypeCommon) {
      filepathR = string("Image/") + _skinPrefix + string("_frame_right.png");
    } else {
      if (manager->getCurrentCharacter()->getCharacterType() == CharacterTypeVox) {
        filepathR = string("Image/") + _skinPrefix + string("_frame_vox_right.png");
      } else {
        filepathR = string("Image/") + _skinPrefix + string("_frame_lsk_right.png");
      }
    }
    CCSprite* rightFrame = CCSprite::create(FileUtils::getFilePath(filepathR.c_str()).c_str());
    rightFrame->setPosition(rightFramePosition);
    
    CCNode* newFrame = CCNode::create();
    newFrame->addChild(leftFrame);
    newFrame->addChild(rightFrame);
    this->addChild(newFrame, ControllerZOrderFrame, controllerFrameTag);
  }
}
