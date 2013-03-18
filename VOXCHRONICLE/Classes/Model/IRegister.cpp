//
//  IRegister.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/3/19.
//
//

#include "IRegister.h"

IRegister::IRegister() {
  _register = new map<string, int>();
}

IRegister::~IRegister() {
  delete _register;
}

int IRegister::getRegister(const char *key, int defaultValue) {
  if (this->hasRegister(key)) {
    return _register->at(key);
  }
  return defaultValue;
}

void IRegister::setRegister(const char *key, int value) {
  if (this->hasRegister(key)) {
    (*_register)[string(key)] = value;
  } else {
    _register->insert(std::pair<string, int>(string(key), value));
  }
}

bool IRegister::hasRegister(const char *key) {
  return _register->count(key) == 1;
}