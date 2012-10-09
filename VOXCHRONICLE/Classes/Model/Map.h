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
#include "LuaObject.h"

using namespace std;
using namespace cocos2d;

class Map :public CCObject {
 private:
  int _endLevel;
  int _initialLevel;
  int _maxLevel;
  const char* _slug;
  vector<string>* _nextMaps;
  string* _name;
  string* _prefix;
  string* _backgroundImageName;
  LuaObject* _lua;
 public:
  Map(const char* mapName);
  ~Map();
  Level* createLevel(int lebel);
  Level* createInitialLevel();
  const char* getPrefixedMusicName(const char* musicName);
  int getMaxLevel();
  int getInitialLevel();
  string* getName();
  
  CCArray* getNextMaps();
};

#endif /* defined(__VOXCHRONICLE__Map__) */
