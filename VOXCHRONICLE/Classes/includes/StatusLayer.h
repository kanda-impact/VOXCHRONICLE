//
//  StatusLayer.h
//  VOXCHRONICLE
//
//  Created by giginet on 2012/12/16.
//
//

#ifndef __VOXCHRONICLE__UILayer__
#define __VOXCHRONICLE__UILayer__

#include <iostream>
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

typedef enum {
  MaxHPLabelTag,
  CurrentHPLabelTag,
  LevelLabelTag,
  LifeGaugeBackgroundTag,
  LifeGaugeTag,
  MPMarkerTag
} StatusLayerPartsTag;

class StatusLayer :public CCLayer {
 private:
  CCArray* _mpChips;
  CCSprite* _timeMarker;
  string _prefix;
  
  void onPauseButtonPressed(CCObject* sender);
 public:
  StatusLayer(const char* scriptName);
  ~StatusLayer();
  void setCurrentHP(int hp);
  void setMaxHP(int hp);
  void setCurrentMP(int mp);
  void setMaxMP(int mp);
  void setMarkerDuration(float d);
  void setLevel(int level);
};

#endif /* defined(__VOXCHRONICLE__UILayer__) */
