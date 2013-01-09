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
#define COMMAND_COUNT 8

using namespace cocos2d;

bool Controller::init() {
  if (!CCLayer::init()) {
    return false;
  }
  _triggers = CCArray::create();
  _triggers->retain();
  _enable = true;
  //const int rotation[] = {0, 30, 60, 0, -30, -60};
  const int x[] = {51.0, 38.0, 110.2, 130.5, 341.8, 375.2, 443.2, 410.2};
  const int y[] = {52.2, 129.2, 107.8, 38.2, 50.8, 111.2, 111.2, 52.0};
  const float scale[] = {0.492, 0.376, 0.376, 0.376, 0.376, 0.376, 0.376, 0.376};
  const float rotation[] = {45.0, 45.0, 45.0, 45.0, 90, 90, 90, 90};
  for (int i = 0; i < COMMAND_COUNT; ++i) {
    SkillTrigger* trigger = new SkillTrigger();
    trigger->setPosition(ccp(x[i], y[i]));
    trigger->getBackground()->setRotation(rotation[i]);
    trigger->getBackground()->setScale(scale[i]);
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
