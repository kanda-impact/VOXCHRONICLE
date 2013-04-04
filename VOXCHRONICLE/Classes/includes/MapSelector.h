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
  unsigned int _effectID;
  void buttonPressed(CCObject* sender);
  CCArray* _nextMaps;
  Map* _selectedMap;
 public:
  virtual void onEnter();
  MapSelector(CCArray* nextMaps);
  ~MapSelector();
  Map* getSelectedMap();
};

#endif /* defined(__VOXCHRONICLE__MapSelector__) */
