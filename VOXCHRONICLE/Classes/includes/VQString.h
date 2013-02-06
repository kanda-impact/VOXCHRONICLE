//
//  VQString.h
//  VOXCHRONICLE
//
//  Created by giginet on 2013/2/6.
//
//

#ifndef __VOXCHRONICLE__VQString__
#define __VOXCHRONICLE__VQString__

#include <iostream>
#include "macros.h"
#include "cocos2d.h"
#include <boost/shared_ptr.hpp>

using namespace std;
using namespace cocos2d;
using namespace boost;

/**
 NSStringのWrapper
 C++の文字列処理がゴミ過ぎてカッとなって作った
 */
class VQString :public CCObject {
#ifdef IS_IOS
  struct NSStringWrapper;
#endif
 private:
  shared_ptr<NSStringWrapper> _string;
 public:
  VQString(const char* str);
  ~VQString();
  string getString();
  const char* getCString();
  string substringWithRange(unsigned int loc, unsigned int len);
  unsigned int length();
};

#endif /* defined(__VOXCHRONICLE__VQString__) */
