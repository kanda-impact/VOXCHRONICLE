//
//  GameOverLayer.h
//  VOXCHRONICLE
//
//  Created by giginet on 2013/1/31.
//
//

#ifndef __VOXCHRONICLE__GameOverLayer__
#define __VOXCHRONICLE__GameOverLayer__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class GameOverLayer :public CCLayer {
 private:
  void addGameOverButtons();
 protected:
  virtual void buildUI();
  void replayButtonPressed(CCObject *sender);
  void titleButtonPressed(CCObject *sender);
 public:
  GameOverLayer();
  ~GameOverLayer();
};


#endif /* defined(__VOXCHRONICLE__GameOverLayer__) */
