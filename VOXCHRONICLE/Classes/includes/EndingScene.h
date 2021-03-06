//
//  EndingScene.h
//  VOXCHRONICLE
//
//  Created by giginet on 2013/2/18.
//
//

#ifndef __VOXCHRONICLE__EndingScene__
#define __VOXCHRONICLE__EndingScene__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class EndingScene :public CCLayer {
private:
  int _musicDuration;
  std::string _achievementId;
  std::string _identifier;
  std::string _music;
  void goToNextScene(CCObject* sender);
  void onEnterTransitionDidFinish();
public:
  EndingScene(const char* endingScript);
  ~EndingScene();
  virtual bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
  virtual void registerWithTouchDispatcher();
};

#endif /* defined(__VOXCHRONICLE__EndingScene__) */
