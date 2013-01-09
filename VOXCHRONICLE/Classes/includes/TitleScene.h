//
//  TitleScene.h
//  VOXCHRONICLE
//
//  Created by giginet on 2012/10/27.
//
//

#ifndef __VOXCHRONICLE__TitleScene__
#define __VOXCHRONICLE__TitleScene__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class TitleScene : public cocos2d::CCLayer {
private:
  virtual bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
  virtual void nextScene(CCLayer* layer);
  virtual void registerWithTouchDispatcher();
  void onStartButtonPressed(CCObject* sender);
  void onDebugButtonPressed(CCObject* sender);
  
public:
  virtual bool init();
  static cocos2d::CCScene* scene();
  void onEnterTransitionDidFinish();
  CREATE_FUNC(TitleScene);
};

#endif /* defined(__VOXCHRONICLE__TitleScene__) */
