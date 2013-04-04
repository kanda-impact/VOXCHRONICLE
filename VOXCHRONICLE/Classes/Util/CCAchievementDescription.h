//
//  CCAchievementDescription.h
//  VOXCHRONICLE
//
//  Created by giginet on 2013/4/1.
//
//

#ifndef __VOXCHRONICLE__CCAchievementDescription__
#define __VOXCHRONICLE__CCAchievementDescription__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class CCAchievementDescription :public CCObject {
 private:
  const char* _identifier;
  const char* _title;
  const char* _unachievedDescription;
  const char* _archievedDescription;
  int _maximumPoints;
  CCTexture2D *_image;
  bool _hidden;
  bool _replayable;
 public:
  const char* getIdentifier();
  const char* getTitle();
  const char* getUnachievedDescription();
  const char* getAchievedDescription();
  int getMaximumPoints();
  bool isHidden();
  bool isReplayable();
  CCTexture2D* getImage();
};

#endif /* defined(__VOXCHRONICLE__CCAchievementDescription__) */
