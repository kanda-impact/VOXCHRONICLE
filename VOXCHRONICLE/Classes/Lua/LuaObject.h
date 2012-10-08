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
using namespace cocos2d;

class LuaObject :public CCObject {
 private:
  void init(const char* scriptName, const char* className);
  CCLuaEngine* _engine;
  const char* _className;
  const char* _scriptName;
  std::string _path;
  float getFloatFromTable(lua_State* state, int index);
  void internalLoadSubTableWithKey(string key, lua_State* state, CCLuaValueDict* dict);
  void loadTable();
 public:
  LuaObject(const char* scriptName);
  LuaObject(const char* scriptName, const char* className);
  ~LuaObject();
  int getInt(const char* key);
  float getNumber(const char* key);
  bool getBoolean(const char* key);
  const char* getString(const char* key);
  lua_CFunction getFunction(const char* key);
  CCLuaValueDict* getTable(const char* key);
  CCLuaValueArray* getArray(const char* key);
  const void* getObject(const char* key);
  CCLuaEngine* getLuaEngine();
  static CCLuaValueDict* loadLuaTableFromFile(const char* scriptName);
  CCLuaValueDict* recursivelyLoadTable(int index);
  static CCLuaValueArray* luaTableToArray(CCLuaValueDict* dict);
};

#endif /* defined(__VOXCHRONICLE__LuaObject__) */
