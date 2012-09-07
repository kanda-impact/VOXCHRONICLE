//
//  Controller.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/8.
//
//

#include "Controller.h"
using namespace cocos2d;

Controller * Controller::create(void) {
	Controller * pRet = new Controller();
	pRet->autorelease();
	return pRet;
}

Controller::Controller() : CCNode() {
  CCSprite* test = CCSprite::create("trigger_bg.png");
  this->addChild(test);
}

Controller::~Controller() {
}