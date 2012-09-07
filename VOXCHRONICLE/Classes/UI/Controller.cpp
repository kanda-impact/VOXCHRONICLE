//
//  Controller.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/8.
//
//

#include "Controller.h"
#include "SkillTrigger.h"
using namespace cocos2d;

Controller * Controller::create(void) {
  Controller * pRet = new Controller();
  pRet->autorelease();
  return pRet;
}

Controller::Controller() : CCNode() {
  _triggers = CCArray::create();
  const int rotation[] = {0, 30, 60, 0, -30, -60};
  const int x[] = {95, 235, 310, 866, 727, 651};
  const int y[] = {298.5, 207, 62, 298.5, 208, 62};
  for (int i = 0; i < 6; ++i) {
    SkillTrigger* trigger = SkillTrigger::create("trigger_bg.png");
    trigger->setPosition(ccp(x[i] / 2.0, y[i] / 2.0));
    trigger->setRotation(rotation[i]);
    if (i < 3) trigger->setScaleX(-1);
    this->addChild(trigger);
    _triggers->addObject(trigger);
  }
}

Controller::~Controller() {
}