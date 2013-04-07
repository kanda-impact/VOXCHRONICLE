//
//  SaveData.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/3/2.
//
//

#include "SaveData.h"
#include "CCAchievementManager.h"
#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>

#include "LuaObject.h"

using namespace boost;

static SaveData* _shared = NULL;
const string countDataPrefix = "count_";

SaveData* SaveData::sharedData() {
  if (_shared == NULL) {
    _shared = new SaveData();
  }
  return _shared;
}

SaveData::SaveData() {
  _countDictionary = CCDictionary::create();
  _countDictionary->retain();
  _achievements = CCArray::create();
  _achievements->retain();
  this->load();
  _achievementInfos = new list<AchievementInfo>();
  LuaObject* lua = LuaObject::create("achievement.lua");
  CCLuaValueArray* array = lua->getArray("saveData");
  for (CCLuaValueArrayIterator it = array->begin(); it != array->end(); ++it) {
    CCLuaValueDict dict = (it->dictValue());
    SaveDataCountKey key = (SaveDataCountKey)dict["1"].floatValue();
    int value = dict["2"].floatValue();
    string identifier = dict["3"].stringValue();
    AchievementInfo info;
    info.key = key;
    info.count = value;
    info.identifier = identifier;
    _achievementInfos->push_back(info);
  }
}

SaveData::~SaveData() {
  delete _achievementInfos;
  _countDictionary->release();
  _achievements->release();
}

void SaveData::save() {
  CCUserDefault* ud = CCUserDefault::sharedUserDefault();
  for (int i = 0; i < SaveDataCountKeyNum; ++i) {
    string key = countDataPrefix + boost::lexical_cast<string>(i);
    int count = this->getCountFor((SaveDataCountKey)i);
    ud->setIntegerForKey(key.c_str(), count);
  }
  CCLog("saved");
  ud->flush();
}

void SaveData::load() {
  CCUserDefault* ud = CCUserDefault::sharedUserDefault();
  for (int i = 0; i < SaveDataCountKeyNum; ++i) {
    string key = countDataPrefix + boost::lexical_cast<string>(i);
    int count = ud->getIntegerForKey(key.c_str());
    CCInteger* data = CCInteger::create(count);
    _countDictionary->setObject(data, key);
  }
  CCLog("loaded");
}

bool SaveData::isClearedMap(const char* mapIdentifier) {
  return CCUserDefault::sharedUserDefault()->getBoolForKey(string(string("map_") + mapIdentifier).c_str());
}

void SaveData::setClearedForMap(const char* mapIdentifier) {
  CCUserDefault::sharedUserDefault()->setBoolForKey(string(string("map_") + mapIdentifier).c_str(), true);
}

int SaveData::getDefeatedCount(const char* enemyIdentifier) {
  return CCUserDefault::sharedUserDefault()->getIntegerForKey(string(string("enemy_") + enemyIdentifier).c_str());
}

void SaveData::addDefeatedCountForEnemy(const char* enemyIdentifier) {
  int current = this->getDefeatedCount(enemyIdentifier);
  CCUserDefault::sharedUserDefault()->setIntegerForKey(string(string("enemy_") + enemyIdentifier).c_str(), current + 1);
}

void SaveData::addCountFor(SaveDataCountKey key) {
  this->addCountFor(key, 1);
}

void SaveData::addCountFor(SaveDataCountKey keynum, int value) {
  string key = countDataPrefix + boost::lexical_cast<string>(keynum);
  int current = this->getCountFor(keynum);
  _countDictionary->setObject(CCInteger::create(current + value), key);
  this->checkUnlockAchievement(keynum, value);
}

int SaveData::getCountFor(SaveDataCountKey keynum) {
  string key = countDataPrefix + boost::lexical_cast<string>(keynum);
  CCInteger* obj = (CCInteger*)_countDictionary->objectForKey(key);
  if (obj) {
    return obj->getValue();
  }
  return 0;
}

bool SaveData::isUnlockAchievement(const char* identifier) {
  CCObject* obj = NULL;
  CCARRAY_FOREACH(_achievements, obj) {
    CCString* str = (CCString*)obj;
    if (strcmp(identifier, str->getCString()) == 0) { // 同じ時
      return true;
    }
  }
  return false;
}


void SaveData::unlockAchievement(const char *identifier) {
  CCAchievementManager* manager = CCAchievementManager::sharedManager();
  if (!this->isUnlockAchievement(identifier)) {
    manager->reportAchievement(identifier, 100, true, bind(&SaveData::onFinishAchievementReporting, this, _1, _2));
  }

}

void SaveData::checkUnlockAchievement(SaveDataCountKey key, int value) {
  // パフォーマンス的にも微妙なのでハードコーディング安定
  for (list<AchievementInfo>::iterator it = _achievementInfos->begin(); it != _achievementInfos->end(); ++it) {
    if ((*it).key == key) {
      if ((*it).count < value) {
        this->unlockAchievement((*it).identifier.c_str());
      }
    }
  }
}

void SaveData::onFinishAchievementReporting(const char* identifier, bool error) {
  if (!error) {
    CCLog("unlock achievement %s !", identifier);
    CCString* str = CCString::create(identifier);
    _achievements->addObject(str);
  }
}

void SaveData::setUnlockedAchievement(const char *identifier) {
  CCString* str = CCString::create(identifier);
  _achievements->addObject(str);
}