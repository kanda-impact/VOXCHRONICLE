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
  int _introCount;
  const char* _slug;
  vector<string>* _nextMaps;
  string* _name;
  string* _prefix;
  string* _backgroundImageName;
  LuaObject* _lua;
  list< pair<string, int> >* _fixedEnemyTable; // 固定モンスターテーブル
 public:
  Map(const char* mapName);
  ~Map();
  Level* createLevel(int lebel);
  Level* createInitialLevel();
  string getPrefixedMusicName(const char* musicName);
  int getMaxLevel();
  int getInitialLevel();
  int getIntroCount();
  string* getName();
  CCArray* getFixedEnemies(int preExp, int currentExp);
  CCArray* getNextMaps();
};

#endif /* defined(__VOXCHRONICLE__Map__) */
