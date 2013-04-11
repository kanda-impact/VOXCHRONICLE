//
//  PopupWindow.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/3/2.
//
//

#include "PopupWindow.h"
#include "SimpleAudioEngine.h"
#include <boost/bind.hpp>

using namespace CocosDenshion;

typedef enum {
  PopupWindowTagMessageWindow
} PopupWindowTag;

PopupWindow* PopupWindow::create(int pages) {
  PopupWindow* window = new PopupWindow(pages);
  window->retain();
  return window;
}

PopupWindow::PopupWindow(int pages) {
  if (this->initWithFile("tutorial_window.png")) {
    CCDirector* director = CCDirector::sharedDirector();
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
    
    CCMenuItemImage* left = CCMenuItemImage::create("tutorial_cursor_left.png",
                                                    "tutorial_cursor_left_pressed.png",
                                                    this,
                                                    menu_selector(PopupWindow::onCursorPressed));
    CCMenuItemImage* right = CCMenuItemImage::create("tutorial_cursor_right.png",
                                                     "tutorial_cursor_right_pressed.png",
                                                     this,
                                                     menu_selector(PopupWindow::onCursorPressed));
    left->setTag(0);
    right->setTag(1);
    CCMenu* cursors = CCMenu::create(left, right, NULL);
    cursors->setPosition(ccp(director->getWinSize().width / 2.0, director->getWinSize().height / 2.0));
    cursors->alignItemsHorizontallyWithPadding(350);
    this->addChild(cursors);
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

void PopupWindow::prevPage() {
  this->setPage(_currentPage - 1);
}

void PopupWindow::nextPage() {
  this->setPage(_currentPage + 1);
}

void PopupWindow::setPage(int page) {
  this->removeAllChildrenWithCleanup(true);
  if (page > 0 && page < _maxPages) {
    _currentPage = page;
    CCNode *next = (CCNode*)_pages->objectAtIndex(_currentPage);
    this->addChild(next);
  }
}

void PopupWindow::setText(int page, const char *headerText, const char *text) {
  CCNode* node = this->getPage(page);
  CCLabelTTF* headerShadow = CCLabelTTF::create(headerText, "Helvetica", 24, CCSizeMake(380, 40), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
  
  CCLabelTTF* header = CCLabelTTF::create(headerText, "Helvetica", 24, CCSizeMake(380, 40), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
  headerShadow->setColor(ccc3(33, 33, 33));
  headerShadow->setPosition(ccp(202, 268));
  header->setPosition(ccp(200, 270));
  node->addChild(headerShadow);
  node->addChild(header);
  MessageWindow* window = new MessageWindow("Helvetica", 16, CCSizeMake(370, 240));
  window->setPosition(ccp(200, 130));
  node->addChild(window, 0, PopupWindowTagMessageWindow);
  window->setLastDelay(INTMAX_MAX);
  window->pushMessage(text);
  window->setOnMessageFinishedFunction(boost::bind(&PopupWindow::onFinishedFunction, this, _1, _2));
  window->setOnMessageUpdatedFunction(boost::bind(&PopupWindow::onUpdateFunction, this, _1, _2));
}

void PopupWindow::onUpdateFunction(VQString *string, MessageWindow *window) {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("message.mp3");
}

void PopupWindow::onFinishedFunction(VQString *string, MessageWindow *window) {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("message_finish.mp3");
}

void PopupWindow::onCursorPressed(cocos2d::CCNode *node) {
  int direction = node->getTag();
  if (direction == 0) {
    SimpleAudioEngine::sharedEngine()->playEffect("window_next.mp3");
    this->prevPage();
  } else {
    if (this->isLastPage()) {
      SimpleAudioEngine::sharedEngine()->playEffect("window_close.mp3");
    } else {
      SimpleAudioEngine::sharedEngine()->playEffect("window_next.mp3");
      this->nextPage();
    }
  }
}

void PopupWindow::onWindowTouched() {
  MessageWindow* window = (MessageWindow*)this->getChildByTag(PopupWindowTagMessageWindow);
  window->finishMessage();
}