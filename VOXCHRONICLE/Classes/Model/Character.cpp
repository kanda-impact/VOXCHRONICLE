//
//  Character.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/28.
//
//

#include <boost/lexical_cast.hpp>
#include "Character.h"
#include "Skill.h"

Character::Character(const char* identifier) {
  stringstream ss;
  ss << "Script/character/" << identifier;
  _lua = new LuaObject(ss.str().c_str());
  //CCLuaValueDict* sks = _lua->getTable("skills");
  _name = string(_lua->getString("name"));
  _type = (CharacterType)_lua->getInt("type");
  _identifier = string(identifier);
}

Character::~Character() {
}

string Character::getName() {
  return _name;
}

string Character::getIdentifier() {
  return _identifier;
}

CharacterType Character::getCharacterType() {
  return _type;
}