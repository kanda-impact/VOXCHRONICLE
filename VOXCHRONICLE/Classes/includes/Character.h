//
//  Character.h
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/28.
//
//

#ifndef __VOXCHRONICLE__Character__
#define __VOXCHRONICLE__Character__

#include <iostream>
#include "cocos2d.h"
#include "LuaObject.h"
#include "Skill.h"

using namespace cocos2d;

typedef enum {
  CharacterTypeVox,
  CharacterTypeLaska
} CharacterType;

class Character :public CCObject {
 private:
  string _name;
  string _identifier;
  string _mapIdentifierCache;
  LuaObject* _lua;
  CharacterType _type;
 public:
  Character(const char* identifier);
  ~Character();
  string getName();
  string getIdentifier();
  CharacterType getCharacterType();
};

#endif /* defined(__VOXCHRONICLE__Character__) */
