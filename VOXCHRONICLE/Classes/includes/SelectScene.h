//
//  SelectScene.h
//  VOXCHRONICLE
//
//  Created by giginet on 2013/2/26.
//
//

#ifndef __VOXCHRONICLE__SelectScene__
#define __VOXCHRONICLE__SelectScene__

#include <iostream>
#include "cocos2d.h"
#include "Map.h"

using namespace std;
using namespace cocos2d;

class SelectScene :public CCLayer {
 private:
  CCArray* _thumbnails;
  void createThumbnails();
  void onEasyButtonPressed(CCObject* sender);
  void onHardButtonPressed(CCObject* sender);
  void onBackButtonPressed(CCObject* sender);
  void startGame(CCObject* sender);
  void disableButtons();
  CCSprite* blinkSprite(CCSprite* sprite, float speed);
  CCNode* buttonNode(const char* key, const char* thumbnail, bool pressed);
  Map* _nextMap;
 public:
  virtual bool init();
  SelectScene();
  ~SelectScene();
  CREATE_FUNC(SelectScene);
};

#endif /* defined(__VOXCHRONICLE__SelectScene__) */
