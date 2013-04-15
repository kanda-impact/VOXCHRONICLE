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
#include "VQString.h"
#include "MessageWindow.h"

using namespace cocos2d;

class PopupWindow :public CCSprite {
 private:
  int _maxPages;
  int _currentPage;
  CCArray* _pages;
  void onCursorPressed(CCNode* node);
  void setPage(int page);
 public:
  static PopupWindow* create(int pages);
  PopupWindow(int pages);
  virtual ~PopupWindow();
  CCNode* getPage(int page);
  int getCurrentPage();
  bool isLastPage();
  bool isMessageEnded();
  void prevPage();
  void nextPage();
  void setText(int page, const char* header, const char* text);
  void onUpdateFunction(VQString* string, MessageWindow* window);
  void onFinishedFunction(VQString* string, MessageWindow* window);
  void onWindowTouched();
  void addImage(const char* filename, CCPoint point);
  void addImage(const char* filename);
  void onPopupStart(CCObject* sender);
  void onPopupAppeared(CCObject* sender);
};

#endif /* defined(__VOXCHRONICLE__PopupWindow__) */
