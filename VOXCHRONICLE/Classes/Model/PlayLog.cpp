//
//  PlayLog.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/4/7.
//
//

#include "PlayLog.h"
#include "LuaObject.h"
#include "CCAchievementManager.h"

PlayLog::PlayLog() {
  _count = new map<int, int>();
  _achievementInfos = new list<AchievementInfo>();
  LuaObject* lua = LuaObject::create("achievement.lua");
  CCLuaValueArray* array = lua->getArray("playLog");
  for (CCLuaValueArrayIterator it = array->begin(); it != array->end(); ++it) {
    CCLuaValueDict dict = (it->dictValue());
    SaveDataCountKey key = (SaveDataCountKey)dict["1"].intValue();
    int value = (SaveDataCountKey)dict["2"].intValue();
    string identifier = dict["3"].stringValue();
    AchievementInfo info;
    info.key = key;
    info.count = value;
    info.identifier = identifier;
    _achievementInfos->push_back(info);
  }
}

void PlayLog::checkAchievement(PlayLogKey key, int value) {
  for (list<AchievementInfo>::iterator it = _achievementInfos->begin(); it != _achievementInfos->end(); ++it) {
    if ((*it).key == key) {
      if ((*it).count < value) {
        CCAchievementManager::sharedManager()->reportAchievement((*it).identifier.c_str(), 100, true, NULL);
      }
    }
  }
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