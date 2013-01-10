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

using namespace cocos2d;

class StatusLayer :public CCLayer {
 private:
  CCLabelAtlas* _maxHPLabel;
  CCLabelAtlas* _currentHPLabel;
  CCLabelAtlas* _levelLabel;
  CCArray* _mpChips;
  CCSprite* _lifeGaugeBackground;
  CCSprite* _lifeGauge;
  
  // デバッグ用表示
  CCLabelTTF* _expLabel;
  CCLabelTTF* _nextExpLabel;
  CCLabelTTF* _mapLabel;
  CCSprite* _timeMarker;
 public:
  StatusLayer();
  ~StatusLayer();
  void setCurrentHP(int hp);
  void setMaxHP(int hp);
  void setCurrentMP(int mp);
  void setMaxMP(int mp);
  void setMarkerDuration(float d);
  void setLevel(int level);
};

#endif /* defined(__VOXCHRONICLE__UILayer__) */
