//
//  LuaObject.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/29.
//
//

#include <sstream>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "LuaObject.h"
#include "LuaBind.h"
#include "FileUtils.h"

using namespace std;
using namespace cocos2d;

bool LuaObject::isInitialized = false;

typedef enum {
  kStructType_INVALID = 0,
  kStructTypePoint,
  kStructTypeSize,
  kStructTypeRect,
} EStructTypes;

LuaObject* LuaObject::create(const char *scriptName) {
  LuaObject* obj = new LuaObject(scriptName);
  obj->autorelease();
  return obj;
}

LuaObject::LuaObject(const char* scriptName) {
  this->init(scriptName, NULL);
}

LuaObject::LuaObject(const char* scriptName, const char* className) {
  this->init(scriptName, className);
}

void LuaObject::init(const char* scriptName, const char* className) {
  _engine = CCLuaEngine::defaultEngine();
  string name(scriptName);
  stringstream ss;
  if (!boost::algorithm::iends_with(name, ".lua")) {
    ss << name << ".lua";
    name = ss.str();
  }
  _path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(FileUtils::getFilePath(name.c_str()).c_str());
  _engine->addSearchPath(_path.substr(0, _path.find_last_of("/")).c_str());
  _scriptName = name.c_str();
  _className = className;
  if (!isInitialized) {
    tolua_Cocos2d_open(_engine->getLuaState());
    tolua_VOXCHRONICLE_open(_engine->getLuaState());
    isInitialized = true;
  }
}

LuaObject::~LuaObject() {
}

int LuaObject::getInt(const char *key) {
  lua_State* L = _engine->getLuaState();
  this->loadTable();
  int table = lua_gettop(L);
  lua_getfield(L, table, key);
  int result = 0;
  if (lua_isnumber(L, lua_gettop(L))) {
    result = lua_tointeger(L, -1);
  }
  lua_pop(L, 1);
  return result;
}

float LuaObject::getNumber(const char *key) {
  lua_State* L = _engine->getLuaState();
  this->loadTable();
  int table = lua_gettop(L);
  lua_getfield(L, table, key);
  float result = 0;
  if (lua_isnumber(L, lua_gettop(L))) {
    result = lua_tointeger(L, -1);
  }
  lua_pop(L, 1);
  return result;
}

bool LuaObject::getBoolean(const char *key) {
  lua_State* L = _engine->getLuaState();
  this->loadTable();
  int table = lua_gettop(L);
  lua_getfield(L, table, key);
  bool result = lua_toboolean(L, -1);
  lua_pop(L, 1);
  return result;
}

const char* LuaObject::getString(const char *key) {
  lua_State* L = _engine->getLuaState();
  this->loadTable();
  int table = lua_gettop(L);
  lua_getfield(L, table, key);
  const char* result = "";
  if (lua_isstring(L, lua_gettop(L))) {
    result = lua_tostring(L, -1);
  }
  lua_pop(L, 1);
  return result;
}

lua_CFunction LuaObject::getFunction(const char *key) {
  lua_State* L = _engine->getLuaState();
  this->loadTable();
  int table = lua_gettop(L);
  lua_getfield(L, table, key);
  lua_CFunction result = lua_tocfunction(L, -1);
  lua_pop(L, 1);
  return result;
}

const void* LuaObject::getObject(const char *key) {
  lua_State* L = _engine->getLuaState();
  this->loadTable();
  int table = lua_gettop(L);
  lua_getfield(L, table, key);
  const void* result = lua_topointer(L, -1);
  lua_pop(L, 1);
  return result;
}

shared_ptr<CCLuaValueDict> LuaObject::getTable() {
  lua_State* L = _engine->getLuaState();
  this->loadTable();
  shared_ptr<CCLuaValueDict> dict = recursivelyLoadTable(lua_gettop(L));
  lua_pop(L, 1);
  return dict;
}

shared_ptr<CCLuaValueDict> LuaObject::getTable(const char* key) {
  this->loadTable();
  lua_State* L = _engine->getLuaState();
  int table = lua_gettop(L);
  lua_getfield(L, table, key);
  shared_ptr<CCLuaValueDict> dict = recursivelyLoadTable(lua_gettop(L));
  lua_pop(L, 1);
  return dict;
}

shared_ptr<CCLuaValueArray> LuaObject::getArray() {
  return LuaObject::luaTableToArray(this->getTable());
}

shared_ptr<CCLuaValueArray> LuaObject::getArray(const char *key) {
  return LuaObject::luaTableToArray(this->getTable(key));
}

CCLuaEngine* LuaObject::getLuaEngine() {
  return _engine;
}

CCLuaEngine* LuaObject::getLuaEngineWithLoad() {
  _engine->cleanStack();
  _engine->executeScriptFile(_path.c_str());
  lua_State* L = _engine->getLuaState();
  if (_className != NULL) {
    lua_getglobal(L, _className);
  }
  return _engine;
}

float LuaObject::getFloatFromTable(lua_State* state, int index) {
  lua_pushinteger(state, index);
  lua_gettable(state, -2);
  float f = (float)lua_tonumber(state, -1);
  lua_pop(state, 1);
  return f;
}

void LuaObject::internalLoadSubTableWithKey(string key, lua_State* state, shared_ptr<CCLuaValueDict> dict){
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
    shared_ptr<CCLuaValueDict> tableDict = this->recursivelyLoadTable(-1);
    if (tableDict != NULL) {
      (*dict)[key] = CCLuaValue::dictValue(*tableDict);
    }
    break;
    }
  }
}

shared_ptr<CCLuaValueDict> LuaObject::recursivelyLoadTable(int index) {
  lua_State* state = this->getLuaEngine()->getLuaState();
  string error = "";
  shared_ptr<CCLuaValueDict> dict = shared_ptr<CCLuaValueDict>(new CCLuaValueDict());
  if (lua_istable(state, index)) {
    lua_pushnil(state); // first key
    while (lua_next(state, -2) != 0) {
      string key = "";
      if (lua_isnumber(state, -2)) {
        int number = (int)lua_tonumber(state, -2);
        key = boost::lexical_cast<string>(number);
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

shared_ptr<CCLuaValueDict> LuaObject::loadLuaTableFromFile(const char* scriptName) {
  LuaObject* obj = LuaObject::create(scriptName);
  shared_ptr<CCLuaValueDict> dict;
  string path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(scriptName);
  obj->getLuaEngine()->executeScriptFile(path.c_str());
  
  lua_State* L = obj->getLuaEngine()->getLuaState();
  
  if (lua_istable(L, -1)) {
    dict = obj->recursivelyLoadTable(-1);
    //LOG_EXPR(dict);
  } else {
    string error = lua_tostring(L, -1);
    cout << "\n\nERROR in loadLuaTableFromFile: " << error << "\n\n";
  }
  
  lua_pop(L, 1);
  return dict;
}

shared_ptr<CCLuaValueArray> LuaObject::luaTableToArray(shared_ptr<CCLuaValueDict> dict) {
  shared_ptr<CCLuaValueArray> array = shared_ptr<CCLuaValueArray>(new CCLuaValueArray());
  for (int i = 1; i <= dict->size(); ++i) {
    array->push_back((*dict)[boost::lexical_cast<string>(i)]);
  }
  return array;
}

void LuaObject::loadTable() {
  _engine->executeScriptFile(_path.c_str());
  lua_State* L = _engine->getLuaState();
  if (_className != NULL) {
    lua_getglobal(L, _className);
  }
}

void LuaObject::pushCCObject(cocos2d::CCObject *object, const char* typeName) {
  _engine->pushCCObject(object, typeName);
}