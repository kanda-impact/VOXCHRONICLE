//
//  Skin.h
//  VOXCHRONICLE
//
//  Created by giginet on 2013/2/19.
//
//

#ifndef __VOXCHRONICLE__Skin__
#define __VOXCHRONICLE__Skin__

#include <iostream>
#include "cocos2d.h"
#include "Ground.h"
#include "StatusLayer.h"
#include "Controller.h"

using namespace cocos2d;

class Skin :public CCObject {
 private:
  Controller* _controller;
  CCSprite* _background;
  Ground* _ground;
  StatusLayer* _statusLayer;
  ControllerFrameType _frameType;
  string _prefix;
 public:
  Skin(const char* scriptName);
  ~Skin();
  CCSprite* getBackground();
  Ground* getGround();
  StatusLayer* getStatusLayer();
  Controller* getController();
  string getPrefix();
  void setController(Controller* controller);
};

#endif /* defined(__VOXCHRONICLE__Skin__) */
