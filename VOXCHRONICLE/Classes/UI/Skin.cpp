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
  LuaObject* lua = LuaObject::create(scriptName);
  int frameCount = lua->getInt("groundFrameCount");
  _prefix = lua->getString("prefix");
  _ground = new Ground(_prefix.c_str(), frameCount);
  _statusLayer = new StatusLayer(scriptName);
  _background = NULL;
  _frameType = (ControllerFrameType)lua->getInt("frameType");
  _controller = NULL;
  if (lua->getBoolean("hasBackground")) {
    string filename = _prefix + "_background.png";
    _background = CCSprite::create(filename.c_str());
    _background->retain();
  }
}

Skin::~Skin() {
  _ground->release();
  _statusLayer->release();
  if (_controller) {
    _controller->release();
  }
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

void Skin::setController(Controller *controller) {
  if (_controller) {
    _controller->release();
  }
  _controller = controller;
  if (controller) {
    controller->retain();
  }
  _controller->setSkinPrefix(_prefix.c_str());
  _controller->setFrameType(_frameType);
}

string Skin::getPrefix() {
  return _prefix;
}