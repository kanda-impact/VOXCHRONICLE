//
//  LuaObject.h
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/29.
//
//

#ifndef __VOXCHRONICLE__LuaObject__
#define __VOXCHRONICLE__LuaObject__

#include <iostream>
#include <string>
#include "LuaCocos2d.h"

using namespace std;

class LuaObject {
 private:
  CCLuaEngine* _engine;
  const char* _className;
  const char* _scriptName;
  std::string _path;
  float getFloatFromTable(lua_State* state, int index);
  void internalLoadSubTableWithKey(string key, lua_State* state, CCLuaValueDict* dict);
 public:
  LuaObject(const char* scriptName, const char* className);
  ~LuaObject();
  int getInt(const char* key);
  float getNumber(const char* key);
  bool getBoolean(const char* key);
  const char* getString(const char* key);
  lua_CFunction getFunction(const char* key);
  const void* getObject(const char* key);
  CCLuaEngine* getLuaEngine();
  CCLuaValueDict* internalRecursivelyLoadTable(lua_State* state, int index);
  CCLuaValueDict* loadLuaTableFromFile(const char* scriptName);
};

#endif /* defined(__VOXCHRONICLE__LuaObject__) */
