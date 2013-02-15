//
//  Species.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/2/15.
//
//

#include "Species.h"
#include "LuaObject.h"

Species::Species(const char* identifier) {
  LuaObject* lua = LuaObject::create(identifier);
  _name = string(lua->getString("name"));
  _attack = lua->getInt("attack");
  _counter = lua->getInt("counter");
  _speed = lua->getInt("speed");
  _minRow = lua->getInt("minRow");
  _imageName = string(lua->getString("imageName"));
  _frameCount = lua->getInt("animationFrames");
}

Species::~Species() {
}

string Species::getImageName() {
  return _imageName;
}

string Species::getName() {
  return _name;
}

int Species::getAttack() {
  return _attack;
}

int Species::getSpeed() {
  return _speed;
}

int Species::getCounter() {
  return _counter;
}

int Species::getMinRow() {
  return _minRow;
}

int Species::getFrameCount() {
  return _frameCount;
}