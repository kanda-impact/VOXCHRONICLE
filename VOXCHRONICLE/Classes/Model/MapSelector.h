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
  CCArray* _nextMaps;
  Map* _selectedMap;
 public:
  virtual bool init();
  MapSelector();
  void setNextMaps(CCArray* maps);
  CREATE_FUNC(MapSelector)
  Map* getSelectedMap();
};

#endif /* defined(__VOXCHRONICLE__MapSelector__) */
