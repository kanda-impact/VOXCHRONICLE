//
//  PauseLayer.h
//  VOXCHRONICLE
//
//  Created by giginet on 2013/1/11.
//
//

#ifndef __VOXCHRONICLE__PauseLayer__
#define __VOXCHRONICLE__PauseLayer__

#include <iostream>
#include "GameOverLayer.h"
#include "cocos2d.h"

using namespace cocos2d;

typedef enum {
  PauseLayerStateTop,
  PauseLayerStateConfirmReplay,
  PauseLayerStateConfirmTitle
} PauseLayerState;

class PauseLayer :public GameOverLayer {
 private:
  CCMenu* _topMenu;
  CCMenu* _confirmMenu;
  CCLabelTTF* _descriptionLabel;
  PauseLayerState _state;
  void changeState(PauseLayerState newState);
  void onReplayPressed(CCObject* sender);
  void onTitlePressed(CCObject* sender);
  void onCancelPressed(CCObject* sender);
  void onYesPressed(CCObject* sender);
  void onNoPressed(CCObject* sender);
  void onPlayPressed();
  virtual void registerWithTouchDispatcher();
  virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
 protected:
  void buildUI();
 public:
  PauseLayer(MainScene* main);
  ~PauseLayer();
};

#endif /* defined(__VOXCHRONICLE__PauseLayer__) */
