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
  LuaObject* _lua;
  CCArray* _skills;
  CharacterType _type;
 public:
  Character(const char* identifier);
  ~Character();
  string getName();
  string getIdentifier();
  CCArray* getSkills();
  CCArray* getSkills(int level);
  CharacterType getCharacterType();
};

#endif /* defined(__VOXCHRONICLE__Character__) */
