//
//  LuaObject.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/29.
//
//

#include <sstream>
#include "LuaObject.h"

using namespace std;
using namespace cocos2d;

typedef enum {
  kStructType_INVALID = 0,
  kStructTypePoint,
  kStructTypeSize,
  kStructTypeRect,
} EStructTypes;

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

float LuaObject::getFloatFromTable(lua_State* state, int index) {
  lua_pushinteger(state, index);
  lua_gettable(state, -2);
  float f = (float)lua_tonumber(state, -1);
  lua_pop(state, 1);
  return f;
}

void LuaObject::internalLoadSubTableWithKey(string key, lua_State* state, CCLuaValueDict* dict){
  // check if the table contains a "magic marker"
  lua_getfield(state, -1, "structType");
  int structType = (int)lua_tointeger(state, -1);
  lua_pop(state, 1);
  
  // create the appropriate NSValue type
  switch (structType) {
    case kStructTypePoint:
    {
    float x = this->getFloatFromTable(state, 1);
    float y = this->getFloatFromTable(state, 2);
    CCPoint p = CCPointMake(x, y);
    (*dict)[key] = CCLuaValue::ccobjectValue(&p, "CCPoint");
    break;
    }
    case kStructTypeSize:
    {
    float width = this->getFloatFromTable(state, 1);
    float height = this->getFloatFromTable(state, 2);
    CCSize size = CCSizeMake(width, height);
    (*dict)[key] = CCLuaValue::ccobjectValue(&size, "CCSize");
    break;
    }
    case kStructTypeRect:
    {
    float x = this->getFloatFromTable(state, 1);
    float y = this->getFloatFromTable(state, 2);
    float width = this->getFloatFromTable(state, 3);
    float height = this->getFloatFromTable(state, 4);
    CCRect rect = CCRectMake(x, y, width, height);
    (*dict)[key] = CCLuaValue::ccobjectValue(&rect, "CCRect");
    break;
    }
      
    default:
    case kStructType_INVALID:
    {
    // assume it's a user table, recurse into it
    CCLuaValueDict* tableDict = this->internalRecursivelyLoadTable(state, -1);
    if (tableDict != NULL) {
      (*dict)[key] = CCLuaValue::dictValue(*tableDict);
    }
    break;
    }
  }
}

CCLuaValueDict* LuaObject::internalRecursivelyLoadTable(lua_State* state, int index) {
  string error = "";
  CCLuaValueDict* dict = NULL;
  if (lua_istable(state, index)) {
    dict = new CCLuaValueDict();
    lua_pushnil(state); // first key
    while (lua_next(state, -2) != 0) {
      string key = "";
      if (lua_isnumber(state, -2)) {
        int number = (int)lua_tonumber(state, -2);
        stringstream ss;
        ss << number;
        key = ss.str();
      } else if (lua_isstring(state, -2)) {
        key = lua_tostring(state, -2);
      } else {
        error = "key in table is neither string nor number!";
        break;
      }
      
      int luaTypeOfValue = lua_type(state, -1);
      switch (luaTypeOfValue) {
        case LUA_TNUMBER:
          (*dict)[key] = CCLuaValue::floatValue((float)lua_tonumber(state, -1));
          break;
        case LUA_TSTRING:
          (*dict)[key] = CCLuaValue::stringValue(lua_tostring(state, -1));
          break;
        case LUA_TBOOLEAN:
          (*dict)[key] = CCLuaValue::booleanValue(lua_toboolean(state, -1));
          break;
        case LUA_TTABLE:
        {
        this->internalLoadSubTableWithKey(key, state, dict);
        break;
        }
          
        default:
          cout << "Unknown value type " << luaTypeOfValue << " in table ignored." << endl;
          break;
      }
      
      lua_pop(state, 1);
    }
  } else {
    error = "not a Lua table!";
  }
  
  if (error.length() != 0) {
    cout << "\n\nERROR in internalRecursivelyLoadTable: " << error << "\n\n" << endl;;
  }
  return dict;
}

CCLuaValueDict* LuaObject::loadLuaTableFromFile(const char* scriptName) {
  CCLuaValueDict* dict = NULL;
  string path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(scriptName);
  _engine->executeScriptFile(path.c_str());
  
  lua_State* L = this->getLuaEngine()->getLuaState();
  
  if (lua_istable(L, -1)) {
    dict = this->internalRecursivelyLoadTable(L, -1);
    //LOG_EXPR(dict);
  } else {
    string error = lua_tostring(L, -1);
    cout << "\n\nERROR in loadLuaTableFromFile: " << error << "\n\n";
  }
  
  lua_pop(L, 1);
  
  return dict;
}