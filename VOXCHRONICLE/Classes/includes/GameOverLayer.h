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
#include "MainScene.h"
#include "cocos2d.h"

using namespace cocos2d;

class GameOverLayer :public CCLayer {
 private:
  MainScene* _main;
  MainBackScene _backScene;
  void addGameOverButtons();
 protected:
  virtual void buildUI();
  virtual void replayButtonPressed(CCObject *sender);
  virtual void titleButtonPressed(CCObject *sender);
 public:
  GameOverLayer(MainScene* main);
  virtual ~GameOverLayer();
  void setMainBackScene(MainBackScene scene);
  virtual bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
  virtual void registerWithTouchDispatcher();
};


#endif /* defined(__VOXCHRONICLE__GameOverLayer__) */
