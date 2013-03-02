//
//  PopupWindow.h
//  VOXCHRONICLE
//
//  Created by giginet on 2013/3/2.
//
//

#ifndef __VOXCHRONICLE__PopupWindow__
#define __VOXCHRONICLE__PopupWindow__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class PopupWindow :public CCSprite {
 private:
  int _maxPages;
  int _currentPage;
  CCArray* _pages;
 public:
  static PopupWindow* create(int pages);
  PopupWindow(int pages);
  virtual ~PopupWindow();
  CCNode* getPage(int page);
  int getCurrentPage();
  bool isLastPage();
  void nextPage();
};

#endif /* defined(__VOXCHRONICLE__PopupWindow__) */
