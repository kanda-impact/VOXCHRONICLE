//
//  Controller.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/8.
//
//

#include "SimpleAudioEngine.h"

#include "Controller.h"
#include "SkillTrigger.h"
#include "FileUtils.h"

using namespace cocos2d;

bool Controller::init() {
  if (!CCLayer::init()) {
    return false;
  }
  _triggers = CCArray::create();
  _triggers->retain();
  _enable = true;
  //const int rotation[] = {0, 30, 60, 0, -30, -60};
  const int x[] = {34.8, 81.3, 79.8, 397.64, 444.4, 397.1};
  const int y[] = {85.5, 110.5, 57.82, 110.5, 85.5, 57.73};
  for (int i = 0; i < 6; ++i) {
    SkillTrigger* trigger = SkillTrigger::create(FileUtils::getFilePath("Image/Main/UI/proto/trigger_vox.png").c_str());
    trigger->setPosition(ccp(x[i], y[i]));
    //trigger->setRotation(rotation[i]);
    this->addChild(trigger);
    _triggers->addObject(trigger);
    this->setTouchEnabled(true);
  }
  return true;
}

Controller::Controller() {
}

Controller::~Controller() {
  _triggers->release();
}

void Controller::registerWithTouchDispatcher() {
  CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool Controller::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent) {
  if (!_enable) return false;
  CCObject* trigger = NULL;
  CCARRAY_FOREACH(_triggers, trigger) {
    CCPoint p = ((SkillTrigger*)trigger)->convertTouchToNodeSpace(pTouch);
    CCSize size = ((SkillTrigger*)trigger)->getContentSize();
    const CCPoint triggerCenter = ccp(size.width / 2.0f, size.height / 2.0f);
    const int triggerRadius = size.width / 2.0;
    if (((SkillTrigger*)trigger)->getSkillButtonState() == SkillButtonStateNormal && ccpDistance(triggerCenter, p) < triggerRadius) {
      this->resetAllTriggers();
      CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/cursor.mp3").c_str());
      ((SkillTrigger*)trigger)->setPress(true);
      break;
    }
  }
  
  return true;
}

void Controller::resetAllTriggers() {
  CCObject* trigger = NULL;
  CCARRAY_FOREACH(_triggers, trigger) {
    ((SkillTrigger*)trigger)->setPress(false);
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
      trigger->setSkillButtonState(SkillButtonStateUnknown);
    } else if (skill->getTensionLevel() > manager->getTension()) {
      // テンションレベルが足りないとき、使用不可状態に
      trigger->setSkillButtonState(SkillButtonStateDisable);
    } else {
      // その他のとき、通常状態に
      trigger->setSkillButtonState(SkillButtonStateNormal);
    }
  }
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
}
