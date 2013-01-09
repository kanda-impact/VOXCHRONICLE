//
//  MusicSet.h
//  VOXCHRONICLE
//
//  Created by giginet on 2012/12/31.
//
//

#ifndef __VOXCHRONICLE__MusicSet__
#define __VOXCHRONICLE__MusicSet__

#include <iostream>
#include <map>
#include <vector>
#include "cocos2d.h"
#include "LuaObject.h"

using namespace std;
using namespace cocos2d;

typedef enum {
  MusicSetTypeWay, // 道中曲
  MusicSetTypeBoss // ボス曲
} MusicSetType;

class MusicSet :public CCObject {
private:
  int _introCount; // イントロの小節数
  int _finishCount; // フィニッシュの小節数
  int _waitCount; // waitの小節数
  CCLuaValueDict* _common; // skillの曲が共通かどうか
  CCLuaValueDict* _ignoreDrums; // ドラムを無視するトラックのリスト
  MusicSetType _type; // 曲の種類 道中曲orボス曲
  string* _name; // 曲名
  string* _composer; // 作曲者
  string* _prefix; // 曲ファイルprefix
  LuaObject* _lua; // Luaオブジェクト
public:
  MusicSet(const char* identifier);
  ~MusicSet();
  string getPrefixedMusicName(const char* musicName);
  bool isCommon(const char* skillName);
  int getIntroCount();
  int getFinishCount();
  int getWaitCount();
  MusicSetType getType();
  void preloadAllTracks();
};

#endif /* defined(__VOXCHRONICLE__MusicSet__) */
