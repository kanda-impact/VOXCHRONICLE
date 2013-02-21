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
  int frameCount = lua->getInt("groundFrameCount");
  string prefix = lua->getString("prefix");
  _ground = new Ground(prefix.c_str(), frameCount);
  _statusLayer = new StatusLayer(scriptName);
  _background = NULL;
  _controller = Controller::create();
  _controller->retain();
  if (lua->getBoolean("hasBackground")) {
    string filename = prefix + "_background.png";
    _background = CCSprite::create(filename.c_str());
    _background->retain();
  }
}

Skin::~Skin() {
  _ground->release();
  _statusLayer->release();
  _controller->release();
  if (_background) {
    _background->release();
  }
}

Ground* Skin::getGround() {
  return _ground;
}

StatusLayer* Skin::getStatusLayer() {
  return _statusLayer;
}

CCSprite* Skin::getBackground() {
  return _background;
}

Controller* Skin::getController() {
  return _controller;
}