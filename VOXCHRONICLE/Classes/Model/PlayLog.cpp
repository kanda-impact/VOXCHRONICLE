//
//  PlayLog.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/4/7.
//
//

#include "PlayLog.h"

PlayLog::PlayLog() {
  _count = new map<int, int>();
}

PlayLog::~PlayLog() {
  delete _count;
}

void PlayLog::addCount(PlayLogKey key) {
  (*_count)[key] += 1;
}

int PlayLog::getCount(PlayLogKey key) {
  return (*_count)[key];
}

void PlayLog::setCount(PlayLogKey key, int value) {
  (*_count)[key] = value;
}

void PlayLog::setGraterCount(PlayLogKey key, int value) {
  if (this->getCount(key) < value) {
    this->setCount(key, value);
  }
}

void PlayLog::setLesserCount(PlayLogKey key, int value) {
  if (this->getCount(key) > value) {
    this->setCount(key, value);
  }
}