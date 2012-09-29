//
//  CharacterManager.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/28.
//
//

#include <sstream>
#include "CharacterManager.h"
#include "Skill.h"

CharacterManager::CharacterManager() {
  CCArray* skills = CCArray::create(new Skill("attack"), new Skill("knockback"), NULL);
  Character* vox = new Character(skills);
  vox->autorelease();
  _characters = CCArray::create(vox, NULL);
  _characters->retain();
  _currentCharacter = vox;
  _repeatCount = 0;
  _waitTurn = 0;
  _currentSkill = NULL;
  _lastSkill = NULL;
}

CharacterManager::~CharacterManager() {
  _characters->release();
  if (_lastSkill) _lastSkill->release();
  if (_currentSkill) _currentSkill->release();
}

Character* CharacterManager::getCurrentCharacter() {
  return _currentCharacter;
}

const char* CharacterManager::performSkill(Skill* skill) {
  if (skill) {
    std::ostringstream os;
    os << _currentCharacter->getSlug() << skill->getSlug() << _repeatCount;
    if (!_lastSkill || _lastSkill->isEqual(skill)) {
      _repeatCount = (_repeatCount + 1) % skill->getMaxRepeat();
    } else {
      _repeatCount = 0;
    }
    this->setLastSkill(skill);
    return os.str().c_str();
  } else {
    _repeatCount = 0;
    this->setLastSkill(skill);
    return "silent";
  }
}

bool CharacterManager::isPerforming() {
  return (_currentSkill && _waitTurn < _currentSkill->getTurn());
}

void CharacterManager::setLastSkill(Skill* skill) {
  if (_lastSkill) {
    _lastSkill->release();
  }
  if (skill) {
    skill->retain();
  }
  _lastSkill = skill;
}

void CharacterManager::setCurrentSkill(Skill* skill) {
  if (_currentSkill) {
    _currentSkill->release();
  }
  if (skill) {
    skill->retain();
  }
  _currentSkill = skill;
}