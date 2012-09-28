//
//  CharacterManager.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/28.
//
//

#include "CharacterManager.h"
#include "Skill.h"

CharacterManager::CharacterManager() {
  CCArray* skills = CCArray::create(new Skill(NULL), NULL);
  Character* vox = new Character(skills);
  _characters = CCArray::create(vox, NULL);
  _characters->retain();
  _currentCharacter = vox;
}

CharacterManager::~CharacterManager() {
  _characters->release();
}

Character* CharacterManager::getCurrentCharacter() {
  return _currentCharacter;
}