//
//  Skill.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/29.
//
//

#include <sstream>
#include <string>
#include <boost/lexical_cast.hpp>
#include "Skill.h"
#include "LuaObject.h"
#include "FileUtils.h"
#include "CharacterManager.h"

using namespace boost;

Skill::Skill(const char* identifier) {
  stringstream ss;
  ss << "Script/skills/" << identifier;
  _lua = new LuaObject(ss.str().c_str(), "Skill");
  _name = string(_lua->getString("name"));
  _identifier = string(_lua->getString("identifier"));
  _mp = _lua->getInt("mp");
  _common = _lua->getBoolean("common");
  _maxRepeat = _lua->getInt("maxRepeat");
  _turn = _lua->getInt("turn");
  _effectFrames = _lua->getInt("effectFrames");
  _tensionLevel = _lua->getInt("tensionLevel");
  _range = (SkillRange)_lua->getInt("skillRange");
  _type = (SkillType)_lua->getInt("skillType");
  _se = _lua->getBoolean("se");
  _loop = _lua->getBoolean("loop");
  _cutinType = _lua->getInt("cutinType");
  _canRepeat = _lua->getBoolean("canRepeat");
  CCLuaValueArray* mes = _lua->getArray("messages");
  
  // エフェクトを先読みしておきます
  for (int i = 0; i < _effectFrames; ++i) {
    const char* frameName = (string(this->getIdentifier()) + lexical_cast<string>(i) + string(".png")).c_str();
    CCTextureCache::sharedTextureCache()->addImage(FileUtils::getFilePath(frameName).c_str());
  }
  
  // アイコンも先読みしておきます
  std::stringstream icon;
  icon << "Images/" + this->getIdentifier() << "_icon.png";
  CCTextureCache::sharedTextureCache()->addImage(FileUtils::getFilePath(icon.str().c_str()).c_str());
  

  // メッセージ一覧を生成します
  _messages = CCArray::create();
  _messages->retain();
  if (mes) {
    for (CCLuaValueArrayIterator it = mes->begin(); it != mes->end(); ++it) {
      CCString* str = CCString::create(it->stringValue());
      _messages->addObject(str);
    }
  }
}

Skill::~Skill() {
  _lua->release();
  _messages->release();
}

string Skill::getName() {
  return _name;
}

string Skill::getIdentifier() {
  return _identifier;
}

int Skill::getTurn() {
  return _turn;
}

int Skill::getMaxRepeat() {
  return _maxRepeat;
}

int Skill::getPower(CCObject* manager) {
  lua_State* L = _lua->getLuaEngineWithLoad()->getLuaState();
  lua_getglobal(L, "Skill");
  int table = lua_gettop(L);
  lua_getfield(L, table, "getPower");
  if (lua_isfunction(L, -1)) {
    // skill.luaにgetTensionRateが実装済みのとき
    _lua->pushCCObject(manager, "CharacterManager");
    if (lua_pcall(L, 1, 1, 0)) {
      cout << lua_tostring(L, lua_gettop(L)) << endl;
    }
    int power = lua_tonumber(L, -1);
    return power;
  }
  return 0;
}

int Skill::getMP() {
  return _mp;
}

bool Skill::isCommon() {
  return _common;
}

SkillRange Skill::getRange() {
  return _range;
}

SkillType Skill::getType() {
  return _type;
}

LuaObject* Skill::getLuaObject() {
  return _lua;
}

int Skill::getAcquirementLV() {
  return _acquirementLV;
}

void Skill::setAcquirementLV(int lv) {
  _acquirementLV = lv;
}

int Skill::getEffectFrames() {
  return _effectFrames;
}

int Skill::getTensionLevel() {
  return _tensionLevel;
}

bool Skill::hasSE() {
  return _se;
}

bool Skill::isLoop() {
  return _loop;
}

bool Skill::canRepeat() {
  return _canRepeat;
}

SkillEffectType Skill::getEffectType() {
  if (_effectFrames == 0) return SkillEffectTypeNone;
  switch (_range) {
    case SkillRangeSingle:
    case SkillRangeBack:
      return SkillEffectTypeTarget;
      break;
    default:
      return SkillEffectTypeAll;
      break;
  }
}

CCArray* Skill::getMessages() {
  return _messages;
}

int Skill::getCutinType() {
  return _cutinType;
}