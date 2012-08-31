//
//  MainScene.h
//  VOXCHRONICLE
//
//  Created by giginet on 2012/8/28.
//
//

#ifndef __VOXCHRONICLE__MainScene__
#define __VOXCHRONICLE__MainScene__

#include <iostream>
#include "cocos2d.h"
#include "Music.h"

class MainScene : public cocos2d::CCLayer {
 private:
  VISS::Music* _music;
  
 public:
  virtual bool init();
  
  LAYER_CREATE_FUNC(MainScene);
};

#endif /* defined(__VOXCHRONICLE__MainScene__) */
