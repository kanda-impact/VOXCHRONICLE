//
//  Map.h
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/30.
//
//

#ifndef __VOXCHRONICLE__Map__
#define __VOXCHRONICLE__Map__

#include <iostream>
#include "cocos2d.h"
#include "Level.h"

using namespace std;
using namespace cocos2d;

class Map :public CCObject {
 private:
  int _endLevel;
  string* _name;
  const char* _slug;
  string* _prefix;
  string* _backgroundImageName;
  CCArray* _nextMaps;
 public:
  Map(const char* mapName);
  ~Map();
  Level* createLevel(int lebel);
  const char* getPrefixedMusicName(const char* musicName);
};

#endif /* defined(__VOXCHRONICLE__Map__) */
