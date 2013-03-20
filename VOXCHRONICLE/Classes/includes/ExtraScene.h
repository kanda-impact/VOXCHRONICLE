//
//  ExtraScene.h
//  VOXCHRONICLE
//
//  Created by giginet on 2013/3/18.
//
//

#ifndef __VOXCHRONICLE__ExtraScene__
#define __VOXCHRONICLE__ExtraScene__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class ExtraScene :public CCLayer {
private:
  void onSoundTestButtonPressed(CCObject* sender);
  void onDictionaryButtonPressed(CCObject* sender);
  void onAchievementButtonPressed(CCObject* sender);
  void onCreditButtonPressed(CCObject* sender);
  void onBackButtonPressed(CCObject* sender);
  void nextScene(CCLayer* layer);
public:
  virtual bool init();
  virtual void onExit();
  CREATE_FUNC(ExtraScene);
};

#endif /* defined(__VOXCHRONICLE__ExtraScene__) */
