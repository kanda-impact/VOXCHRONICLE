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

#include "LuaObject.h"

using namespace cocos2d;

class TitleScene : public cocos2d::CCLayer, cocos2d::CCAccelerometerDelegate {
private:
  virtual void nextScene(CCLayer* layer);
  void onStartButtonPressed(CCObject* sender);
  void onDebugButtonPressed(CCObject* sender);
  void onSETogglePressed(CCObject* sender);
  void onDemoStart();
  void onDemoEnd();
  void removeDemo();
  bool _isDemo;
  CCNode* _touchToStart;
  LuaObject* _demo;
public:
  virtual bool init();
  virtual ~TitleScene();
  static cocos2d::CCScene* scene();
  void onEnterTransitionDidFinish();
  bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
  void registerWithTouchDispatcher();
  virtual void 	didAccelerate (CCAcceleration *pAccelerationValue);
  CREATE_FUNC(TitleScene);
};

#endif /* defined(__VOXCHRONICLE__TitleScene__) */
