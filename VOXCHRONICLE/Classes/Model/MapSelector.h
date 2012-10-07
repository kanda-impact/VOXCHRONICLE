//
//  MapSelector.h
//  VOXCHRONICLE
//
//  Created by giginet on 2012/10/7.
//
//

#ifndef __VOXCHRONICLE__MapSelector__
#define __VOXCHRONICLE__MapSelector__

#include <iostream>
#include "cocos2d.h"
#include "Map.h"

using namespace cocos2d;
class MapSelector :public CCLayer {
 private:
  void leftButtonPressed(CCObject* sender);
  void rightButtonPressed(CCObject* sender);
 public:
  virtual bool init();
  MapSelector();
  CREATE_FUNC(MapSelector)
};

#endif /* defined(__VOXCHRONICLE__MapSelector__) */
