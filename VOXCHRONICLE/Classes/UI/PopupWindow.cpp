//
//  PopupWindow.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/3/2.
//
//

#include "PopupWindow.h"

PopupWindow* PopupWindow::create(int pages) {
  PopupWindow* window = new PopupWindow(pages);
  window->retain();
  return window;
}

PopupWindow::PopupWindow(int pages) {
  if (this->initWithFile("tutorial_window.png")) {
    _maxPages = pages;
    _currentPage = 0;
    _pages = CCArray::create();
    _pages->retain();
    for (int i = 0; i < pages; ++i) {
      CCNode* node = CCNode::create();
      _pages->addObject(node);
    }
    CCNode* root = (CCNode*)_pages->objectAtIndex(0);
    this->addChild(root);
  }
}

PopupWindow::~PopupWindow() {
  _pages->release();
}

CCNode* PopupWindow::getPage(int page) {
  return (CCNode*)_pages->objectAtIndex(page);
}

int PopupWindow::getCurrentPage() {
  return _currentPage;
}

bool PopupWindow::isLastPage() {
  return _maxPages - 1 <= _currentPage;
}

void PopupWindow::nextPage() {
  this->removeAllChildrenWithCleanup(true);
  if (!this->isLastPage()) {
    ++_currentPage;
    CCNode *next = (CCNode*)_pages->objectAtIndex(_currentPage);
    this->addChild(next);
  }
}