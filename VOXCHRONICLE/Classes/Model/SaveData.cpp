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
    _shared->load();
  }
  return _shared;
}

SaveData::SaveData() {
  _clearedMaps = CCArray::create();
  _clearedMaps->retain();
  _defeatedCount = CCDictionary::create();
  _defeatedCount->retain();
  _dirty = true;
}

SaveData::~SaveData() {
  _clearedMaps->release();
  _defeatedCount->release();
}

bool SaveData::load() {
  if (_dirty) {
    CCUserDefault* ud = CCUserDefault::sharedUserDefault();
    return true;
  }
  return false;
}

bool SaveData::save() {
  return false;
}

CCArray* SaveData::getClearedMaps() {
  return _clearedMaps;
}

void SaveData::markClearedForMap(Map *map) {
  CCString* str = CCString::create(map->getIdentifier());
  _clearedMaps->addObject(str);
}
