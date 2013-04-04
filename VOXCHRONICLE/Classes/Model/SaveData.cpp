//
//  SaveData.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/3/2.
//
//

#include "SaveData.h"
#include <boost/lexical_cast.hpp>

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
  this->load();
}

SaveData::~SaveData() {
}

void SaveData::save() {
  CCUserDefault* ud = CCUserDefault::sharedUserDefault();
  for (int i = 0; i < SaveDataCountKeyNum; ++i) {
    string key = countDataPrefix + boost::lexical_cast<string>(i);
    int count = ((CCInteger*)_countDictionary->objectForKey(key))->getValue();
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
  CCUserDefault::sharedUserDefault()->setBoolForKey(string(string("enemy_") + enemyIdentifier).c_str(), current + 1);
}

void SaveData::addCountFor(SaveDataCountKey keynum) {
  string key = countDataPrefix + boost::lexical_cast<string>(keynum);
  int current = this->getCountFor(keynum);
  _countDictionary->setObject(CCInteger::create(current + 1), key);
}

int SaveData::getCountFor(SaveDataCountKey keynum) {
  string key = countDataPrefix + boost::lexical_cast<string>(keynum);
  int count = ((CCInteger*)_countDictionary->objectForKey(key))->getValue();
  return count;
}