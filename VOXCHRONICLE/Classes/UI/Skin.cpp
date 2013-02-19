//
//  Skin.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/2/19.
//
//

#include "Skin.h"
#include "LuaObject.h"

Skin::Skin(const char* scriptName) {
  LuaObject* lua = new LuaObject(scriptName);
  int frameCount = lua->getInt("backgroundFrameCount");
  string prefix = lua->getString("prefix");
  _ground = new Ground(prefix.c_str(), frameCount);
  _ground->retain();
  _statusLayer = new StatusLayer();
  _statusLayer->retain();
}

Skin::~Skin() {
  _ground->release();
  _statusLayer->release();
}