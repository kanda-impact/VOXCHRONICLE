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
  _count = new map<PlayLogKey, int>();
  _achievementInfos = new list<AchievementInfo>();
  _mapHistory = CCArray::create();
  _mapHistory->retain();
  LuaObject* lua = LuaObject::create("achievement.lua");
  CCLuaValueArray* array = lua->getArray("playLog");
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

void PlayLog::checkAchievement(PlayLogKey key, int value) {
  for (list<AchievementInfo>::iterator it = _achievementInfos->begin(); it != _achievementInfos->end(); ++it) {
    AchievementInfo info = (*it);
    if ((*it).key == key) {
      if ((*it).count <= value) {
        SaveData::sharedData()->unlockAchievement((*it).identifier.c_str());
      }
    }
  }
}

PlayLog::~PlayLog() {
  delete _count;
  _mapHistory->release();
}

void PlayLog::addCount(PlayLogKey key) {
  int value = this->getCount(key);
  this->setCount(key, value + 1);
}

int PlayLog::getCount(int key) {
  if (_count->count((PlayLogKey)key)) {
    return (*_count)[(PlayLogKey)key];
  }
  return 0;
}

void PlayLog::setCount(PlayLogKey key, int value) {
  (*_count)[key] = value;
  this->checkAchievement(key, value);
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

CCArray* PlayLog::getMapHistory() {
  return _mapHistory;
}

void PlayLog::checkAchievementsOnClear(CharacterManager *characterManager, EnemyManager *enemyManager) {
  LuaObject* lua = LuaObject::create("achievement.lua");
  lua_State* L = lua->getLuaEngineWithLoad()->getLuaState();
  lua_getfield(L, lua_gettop(L), "checkAchievementOnClear");
  if (lua_isfunction(L, lua_gettop(L))) {
    lua->pushCCObject(this, "PlayLog");
    lua->pushCCObject(characterManager, "CharacterManager");
    lua->pushCCObject(enemyManager, "EnemyManager");
    if (lua_pcall(L, 3, 0, 0)) {
      cout << lua_tostring(L, lua_gettop(L)) << endl;
    }
  }
}

void PlayLog::setSkillCount(Skill* skill, CharacterManager *_characterManager) {
  //CharacterType type = _characterManager->getCurrentCharacter()->getCharacterType();
  if (skill == NULL) return;
  Skill* lastSkill = _characterManager->getLastSkill();
  if (lastSkill && skill->getIdentifier() == lastSkill->getIdentifier()) { // 前回と同じ時
    int count = _characterManager->getRepeatCountRaw();
    if (skill->getIdentifier() == "change") {
      this->setGraterCount(PlayLogKeyMaxRepeatChangeCount, count + 2);
    } else {
      this->setGraterCount(PlayLogKeyMaxRepeatCount, count + 2);
    }
  }
  if (skill->getIdentifier() == "attack") {
    this->addCount(PlayLogKeyVOXAttackCount);
  } else if (skill->getIdentifier() == "magic") {
    this->addCount(PlayLogKeyLSKAttackCount);
  } else if (skill->getIdentifier() == "run") {
    this->addCount(PlayLogKeyRunCount);
  } else if (skill->getIdentifier() == "change") {
    this->addCount(PlayLogKeyChangeCount);
  } else if (skill->getIdentifier() == "tension") {
    this->addCount(PlayLogKeyTensionCount);
  }
}