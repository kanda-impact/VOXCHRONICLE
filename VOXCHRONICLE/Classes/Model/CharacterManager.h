//
//  CharacterManager.h
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/28.
//
//

#ifndef __VOXCHRONICLE__CharacterManager__
#define __VOXCHRONICLE__CharacterManager__

#include <iostream>
#include "Character.h"

class CharacterManager {
 private:
  int _hp;
  int _mp;
  Character* _currentCharacter;
  CCArray* _characters;
 public:
  CharacterManager();
  ~CharacterManager();
};

#endif /* defined(__VOXCHRONICLE__CharacterManager__) */
