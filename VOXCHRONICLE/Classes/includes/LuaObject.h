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
#include <boost/shared_ptr.hpp>

using namespace std;
using namespace cocos2d;
using namespace boost;

class LuaObject :public CCObject {
 private:
  void init(const char* scriptName, const char* className);
  CCLuaEngine* _engine;
  const char* _className;
  const char* _scriptName;
  std::string _path;
  float getFloatFromTable(lua_State* state, int index);
  void internalLoadSubTableWithKey(string key, lua_State* state, shared_ptr<CCLuaValueDict> dict);
  void loadTable();
  static bool isInitialized;
 public:
  static LuaObject* create(const char* scriptName);
  LuaObject(const char* scriptName);
  LuaObject(const char* scriptName, const char* className);
  ~LuaObject();
  int getInt(const char* key);
  float getNumber(const char* key);
  bool getBoolean(const char* key);
  const char* getString(const char* key);
  lua_CFunction getFunction(const char* key);
  shared_ptr<CCLuaValueDict> getTable();
  shared_ptr<CCLuaValueDict> getTable(const char* key);
  shared_ptr<CCLuaValueArray> getArray();
  shared_ptr<CCLuaValueArray> getArray(const char* key);
  const void* getObject(const char* key);
  CCLuaEngine* getLuaEngine();
  CCLuaEngine* getLuaEngineWithLoad();
  void pushCCObject(CCObject* object, const char* typeName);
  static shared_ptr<CCLuaValueDict> loadLuaTableFromFile(const char* scriptName);
  shared_ptr<CCLuaValueDict> recursivelyLoadTable(int index);
  static shared_ptr<CCLuaValueArray> luaTableToArray(shared_ptr<CCLuaValueDict> dict);
};

#endif /* defined(__VOXCHRONICLE__LuaObject__) */
