//
//  EnemySkill.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/12/31.
//
//

#include "EnemySkill.h"
#include "sstream"

EnemySkill::EnemySkill(const char* identifier) {
  stringstream ss;
  ss << "Script/enemySkills/" << identifier << ".lua";
  _lua = new LuaObject(ss.str().c_str());
  _lua->retain();
  _name = _lua->getString("name");
}

EnemySkill::~EnemySkill() {
  _lua->release();
}

void EnemySkill::performSkill(Enemy *user, CharacterManager *characterManager, EnemyManager *enemyManager) {
  lua_State* L = _lua->getLuaEngineWithLoad()->getLuaState();
  lua_getfield(L, lua_gettop(L), "performSkill");
  if (lua_isfunction(L, lua_gettop(L))) {
    _lua->pushCCObject(this, "EnemySkill");
    _lua->pushCCObject(user, "Enemy");
    _lua->pushCCObject(characterManager, "CharacterManager");
    _lua->getLuaEngine()->pushCCObject(enemyManager, "EnemyManager");
    if (lua_pcall(L, 4, 1, 0)) {
      cout << lua_tostring(L, lua_gettop(L)) << endl;
    }
  }
}