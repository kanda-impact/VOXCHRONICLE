//
//  LuaObject.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/29.
//
//
#include "LuaObject.h"

LuaObject::LuaObject(const char* scriptName, const char* className) {
  _engine = CCLuaEngine::create();
  _path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(scriptName);
  _engine->addSearchPath(_path.substr(0, _path.find_last_of("/")).c_str());
  _engine->executeScriptFile(_path.c_str());
  _scriptName = scriptName;
  _className = className;
}

LuaObject::~LuaObject() {
  delete _engine;
}

int LuaObject::getInt(const char *key) {
  _engine->executeScriptFile(_path.c_str());
  lua_State* L = _engine->getLuaState();
  lua_getglobal(L, _className);
  int table = lua_gettop(L);
  lua_getfield(L, table, key);
  int result = lua_tointeger(L, -1);
  lua_pop(L, 1);
  return result;
}

float LuaObject::getNumber(const char *key) {
  _engine->executeScriptFile(_path.c_str());
  lua_State* L = _engine->getLuaState();
  lua_getglobal(L, _className);
  int table = lua_gettop(L);
  lua_getfield(L, table, key);
  float result = lua_tonumber(L, -1);
  lua_pop(L, 1);
  return result;
}

bool LuaObject::getBoolean(const char *key) {
  _engine->executeScriptFile(_path.c_str());
  lua_State* L = _engine->getLuaState();
  lua_getglobal(L, _className);
  int table = lua_gettop(L);
  lua_getfield(L, table, key);
  bool result = lua_toboolean(L, -1);
  lua_pop(L, 1);
  return result;
}

const char* LuaObject::getString(const char *key) {
  _engine->executeScriptFile(_path.c_str());
  lua_State* L = _engine->getLuaState();
  lua_getglobal(L, _className);
  int table = lua_gettop(L);
  lua_getfield(L, table, key);
  const char* result = lua_tostring(L, -1);
  lua_pop(L, 1);
  return result;
}

lua_CFunction LuaObject::getFunction(const char *key) {
  _engine->executeScriptFile(_path.c_str());
  lua_State* L = _engine->getLuaState();
  lua_getglobal(L, _className);
  int table = lua_gettop(L);
  lua_getfield(L, table, key);
  lua_CFunction result = lua_tocfunction(L, -1);
  lua_pop(L, 1);
  return result;
}

const void* LuaObject::getObject(const char *key) {
  _engine->executeScriptFile(_path.c_str());
  lua_State* L = _engine->getLuaState();
  lua_getglobal(L, _className);
  int table = lua_gettop(L);
  lua_getfield(L, table, key);
  const void* result = lua_topointer(L, -1);
  lua_pop(L, 1);
  return result;
}

CCLuaEngine* LuaObject::getLuaEngine() {
  return _engine;
}