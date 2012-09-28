//
//  Skill.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/29.
//
//

#include <sstream>
#include "Skill.h"
#include "LuaCocos2d.h"

Skill::Skill(const char* slug) {
  std::ostringstream os;
  os << slug << ".lua";
  CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
  CCScriptEngineManager::sharedManager()->setScriptEngine(pEngine);
  std::string path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(os.str().c_str());
  pEngine->addSearchPath(path.substr(0, path.find_last_of("/")).c_str());
  pEngine->executeScriptFile(path.c_str());
  lua_State* L = pEngine->getLuaState();
  lua_getglobal(L, "skill");
  int table = lua_gettop(L);
  // テスト用にハードコード
  lua_getfield(L, table, "name");
  _name = lua_tostring(L, -1);
  lua_pop(L, 1);
  _slug = slug;
  lua_getfield(L, table, "power");
  _power = lua_tointeger(L, -1);
  lua_pop(L, 1);
  lua_getfield(L, table, "maxRepeat");
  _maxRepeat = lua_tointeger(L, -1);
  lua_pop(L, 1);
  lua_getfield(L, table, "turn");
  _turn = lua_tointeger(L, -1);
  lua_pop(L, 1);
  lua_getfield(L, table, "skillRange");
  _range = (SkillRange)lua_tointeger(L, -1);
  lua_pop(L, 1);
  lua_getfield(L, table, "skillType");
  _type = (SkillType)lua_tointeger(L, -1);
  lua_pop(L, 1);
}

Skill::~Skill() {
}

const char* Skill::getName() {
  return _name;
}

const char* Skill::getSlug() {
  return _slug;
}

int Skill::getTurn() {
  return _turn;
}

int Skill::getMaxRepeat() {
  return _maxRepeat;
}

int Skill::getPower() {
  return _power;
}

SkillRange Skill::getRange() {
  return _range;
}

SkillType Skill::getType() {
  return _type;
}