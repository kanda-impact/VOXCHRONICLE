//
//  Map.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/30.
//
//

#include <sstream>
#include "Map.h"
#include "Level.h"
#include "LuaObject.h"
#include "Enemy.h"
#include "FileUtils.h"
#include <boost/lexical_cast.hpp>

using namespace std;

Map::Map(const char* mapName) {
  // ここでスクリプトを読ませる
  stringstream ss;
  ss << "Script/map/" << mapName;
  _identifier = mapName;
  _background = NULL;
  _lua = new LuaObject(ss.str().c_str(), "Map");
  _skillCache = NULL;
  
  // スキンの生成
  _skin = new Skin(_lua->getString("skin"));
  
  // MusicSetの生成
  string wayMusicName = _lua->getString("wayMusic");
  string bossMusicName = _lua->getString("bossMusic");
  _wayMusic = new MusicSet(wayMusicName.c_str());
  _wayMusic->retain();
  _bossMusic = NULL;
  if (bossMusicName.length() > 0) {
    _bossMusic = new MusicSet(bossMusicName.c_str());
    _bossMusic->retain();
  }
  
  // スクリプトから各種データ読み込み
  _name = _lua->getString("name");
  _backgroundImageName = _lua->getString("backgroundImage");
  _ending = _lua->getString("ending");
  CCLuaValueArray* nexts = _lua->getArray("nextMaps");
  _initialLevel = _lua->getInt("initialLevel");
  _maxLevel = _lua->getInt("maxLevel");
  _nextMaps = new vector<string>();
  _fixedEnemyTable = new list< pair<string, int> >();
  for (CCLuaValueArray::const_iterator it = nexts->begin(); it != nexts->end(); ++it) {
    _nextMaps->push_back(it->stringValue());
  }
  
  CCLuaValueDict* table = _lua->getTable("fixedEnemies");
  if (table) {
    for (CCLuaValueDictIterator it = table->begin(); it != table->end(); ++it) {
      if (it->second.getType() != CCLuaValueTypeDict) {
        assert("fixedEnemies must contain array only.");
      }
      CCLuaValueDict array = it->second.dictValue();
      string enemy = array["1"].stringValue();
      int exp = array["2"].floatValue();
      pair<string, int> table(enemy, exp);
      _fixedEnemyTable->push_back(table);
    }
  }
}

Map::~Map() {
  delete _fixedEnemyTable;
  if (_wayMusic != NULL) {
    _wayMusic->release();
  }
  if (_bossMusic != NULL) {
    _bossMusic->release();
  }
  if (_background != NULL) {
    _background->release();
  }
  if (_skillCache != NULL) {
    _skillCache->release();
  }
  _lua->release();
  _skin->release();
}

Level* Map::createLevel(int level, CharacterManager* manager) {
  Level* lv = new Level(level, this);
  // モンスターテーブルを設定
  lua_State* L = _lua->getLuaEngineWithLoad()->getLuaState();
  lua_getfield(L, lua_gettop(L), "getEnemyTable");
  if (lua_isfunction(L, lua_gettop(L))) {
    lua_pushinteger(L, level);
    if (lua_pcall(L, 1, 1, 0)) {
      cout << lua_tostring(L, lua_gettop(L)) << endl;
    }
    list< pair<string, int> > enemyTable;
    CCLuaValueDict* dict = _lua->recursivelyLoadTable(lua_gettop(L));
    for (CCLuaValueDictIterator it = dict->begin(); it != dict->end(); ++it) {
      string key = it->first;
      CCLuaValue value = it->second;
      enemyTable.push_back( pair<string, int>(key, (int)value.floatValue()) );
    }
    lv->setEnemyTable(enemyTable);
  }
  
  // モンスター出現率を設定
  lua_getglobal(L, "Map");
  lua_getfield(L, lua_gettop(L), "getEnemyPopRate");
  if (lua_isfunction(L, lua_gettop(L))) {
    lua_pushinteger(L, level);
    if (lua_pcall(L, 1, 1, 0)) {
      cout << lua_tostring(L, lua_gettop(L)) << endl;
    }
    float enemyPopRate = lua_tonumber(L, lua_gettop(L));
    lv->setEnemyPopRate(enemyPopRate);
  }
  
  // 技の読み込み
  if (_skillCache == NULL) {
    _skillCache = CCDictionary::create();
    _skillCache->retain();
    CCObject* obj = NULL;
    CCARRAY_FOREACH(manager->getCharacters(), obj) {
      Character* chara = (Character*)obj;
      this->loadSkillTable(chara);
    }
  }
  lv->setSkillTable(_skillCache);
  return lv;
}

Level* Map::createInitialLevel(CharacterManager* manager) {
  return this->createLevel(_initialLevel, manager);
}

int Map::getMaxLevel() {
  return _maxLevel;
}

int Map::getInitialLevel() {
  return _initialLevel;
  
}

CCArray* Map::getNextMaps() {
  CCArray* maps = CCArray::create();
  for (vector<string>::iterator it = _nextMaps->begin(); it != _nextMaps->end(); ++it) {
    Map* newMap = new Map(it->c_str());
    maps->addObject(newMap);
  }
  return maps;
}

string Map::getName() {
  return _name;
}

string Map::getIdentifier() {
  return _identifier;
}

CCArray* Map::getFixedEnemies(int preExp, int currentExp) {
  CCArray* enemies = CCArray::create();
  list< pair<string, int> > poped;
  for (list< pair<string, int> >::iterator it = _fixedEnemyTable->begin(); it != _fixedEnemyTable->end(); ++it) {
    int exp = it->second;
    if (exp <= currentExp ) {
      CCString* str = CCString::create(it->first);
      enemies->addObject(str);
      poped.push_back(*it);
    }
  }
  for (list< pair<string, int> >::iterator it = poped.begin(); it != poped.end(); ++it) {
    _fixedEnemyTable->remove(*it);
  }
  return enemies;
}

bool Map::isBossStage() {
  return _bossMusic != NULL;
}

MusicSet* Map::getCurrentMusic(Level *level) {
  if (level->getLevel() >= _maxLevel) {
    return _bossMusic;
  }
  return _wayMusic;
}

void Map::performFunction(const char* function, CharacterManager *characterManager, EnemyManager *enemyManager) {
  lua_State* L = _lua->getLuaEngineWithLoad()->getLuaState();
  lua_getglobal(L, "Map");
  int table = lua_gettop(L);
  lua_getfield(L, table, function);
  if (lua_isfunction(L,  lua_gettop(L))) {
    _lua->pushCCObject(this, "Map");
    _lua->pushCCObject(characterManager, "CharacterManager");
    _lua->pushCCObject(enemyManager, "EnemyManager");
    if (lua_pcall(L, 3, 0, 0)) {
      cout << lua_tostring(L, lua_gettop(L)) << endl;
    }
  }

}

void Map::performOnLevel(CharacterManager* characterManager, EnemyManager *enemyManager) {
  this->performFunction("onLevelUp", characterManager, enemyManager);
}

void Map::performOnBack(CharacterManager* characterManager, EnemyManager *enemyManager) {
  this->performFunction("onBack", characterManager, enemyManager);
}

void Map::performOnFinishPlaying(CharacterManager *characterManager, EnemyManager *enemyManager) {
  this->performFunction("onFinishPlaying", characterManager, enemyManager);
}

string Map::getEndingName() {
  return _ending;
}

Skin* Map::getSkin() {
  return _skin;
}

CCSprite* Map::getBackground() {
  if (_backgroundImageName.length() == 0) {
    return NULL;
  }
  if (_background == NULL) {
    _background = CCSprite::create(_backgroundImageName.c_str());
    _background->retain();
  }
  return _background;
}

void Map::loadSkillTable(Character* character) {
  CCArray* skills = CCArray::create();
  LuaObject* lua = LuaObject::create(character->getIdentifier().c_str());
  lua_State* L = lua->getLuaEngineWithLoad()->getLuaState();
  lua_getfield(L, lua_gettop(L), "getSkills");
  if (lua_isfunction(L, lua_gettop(L))) {
    lua_pushstring(L, this->getIdentifier().c_str()); // Map名をpushしてやる
    if (lua_pcall(L, 1, 1, 0)) {
      cout << lua_tostring(L, lua_gettop(L)) << endl;
    }
    CCLuaValueDict* sks = lua->recursivelyLoadTable(lua_gettop(L));
    for (int i = 1; i <= sks->size(); ++i) {
      CCLuaValueDict a = (*sks)[boost::lexical_cast<string>(i).c_str()].dictValue();
      string skillName;
      int alv = 0;
      for (int i = 1; i <= 2; ++i) {
        if (i == 1) {
          skillName = a["1"].stringValue();
        } else if (i == 2){
          alv = a["2"].floatValue();
        }
      }
      Skill* skill = new Skill(skillName.c_str());
      skill->setAcquirementLV(alv);
      skills->addObject(skill);
    }
    _skillCache->setObject(skills, character->getIdentifier());
  }
}

MusicSet* Map::getWayMusic() {
  return _wayMusic;
}

MusicSet* Map::getBossMusic() {
  return _bossMusic;
}