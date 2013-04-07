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

void PopupWindow::setText(int page, const char *headerText, const char *text) {
  CCNode* node = this->getPage(page);
  CCLabelTTF* headerShadow = CCLabelTTF::create(headerText, "Helvetica", 24, CCSizeMake(380, 40), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
  
  CCLabelTTF* header = CCLabelTTF::create(headerText, "Helvetica", 24, CCSizeMake(380, 40), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
  headerShadow->setColor(ccc3(33, 33, 33));
  headerShadow->setPosition(ccp(217, 268));
  header->setPosition(ccp(200, 270));
  node->addChild(headerShadow);
  node->addChild(header);
  MessageWindow* window = new MessageWindow("Helvetica", 16, CCSizeMake(380, 240));
  window->setPosition(ccp(200, 130));
  node->addChild(window);
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