//
//  SaveData.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/3/2.
//
//

#include "SaveData.h"

static SaveData* _shared = NULL;

SaveData* SaveData::sharedData() {
  if (_shared == NULL) {
    _shared = new SaveData();
  }
  return _shared;
}

SaveData::SaveData() {
}

SaveData::~SaveData() {
}

void SaveData::save() {
  CCLog("saved");
  CCUserDefault::sharedUserDefault()->flush();
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