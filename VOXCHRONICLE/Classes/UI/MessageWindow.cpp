//
//  MessageWindow.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/10/20.
//
//

#include "MessageWindow.h"
#include <sstream>

const int kDefaultMessageWindowDelay = 3.0f;
const int kDefaultMessageWindowSpeed = 1.0f;

MessageWindow::MessageWindow(const char* fontName, float size, CCSize dimensions) {
  _messageQueue = CCArray::create();
  _messageQueue->retain();
  _textIndex = 0;
  _textTimer = 0;
  _delay = kDefaultMessageWindowDelay;
  _messageSpeed = kDefaultMessageWindowSpeed;
  this->scheduleUpdate();
  _label = CCLabelTTF::create("", fontName, size, dimensions, kCCTextAlignmentLeft);
  _label->retain();
  _label->setColor(ccc3(255, 255, 255));
  this->addChild(_label);
  _onFinishedFunction = NULL;
  _onUpdatedFunction = NULL;
  _ended = false;
}

MessageWindow::~MessageWindow() {
  _messageQueue->release();
  _label->release();
}

void MessageWindow::pushMessage(const char* message) {
  VQString* str = VQString::create(message);
  _messageQueue->addObject(str);
}

void MessageWindow::update(float dt) {
  _label->setString(this->getCurrentMessage()->getCString());
  if (_messageQueue->count() == 0) return;
  if (this->isEndMessage()) return;
  if (_textIndex <= this->getCurrentWholeMessage()->length() - 1) {
    _textTimer += _messageSpeed;
  }
  int updated = floor(_textTimer);
  if (updated >= 1) {
    if (_onUpdatedFunction) {
      _onUpdatedFunction(this->getCurrentWholeMessage()->substringWithRange(_textIndex, updated), this);
    }
    _textTimer -= updated;
    _textIndex += updated;
  }
  if (!_ended && _textIndex > this->getCurrentWholeMessage()->length() - 1) {
    _ended = true;
    _textIndex = this->getCurrentWholeMessage()->length() - 1;
    if (_onFinishedFunction) {
      _onFinishedFunction(this->getCurrentWholeMessage(), this);
    }
    SEL_SCHEDULE sel = (SEL_SCHEDULE)schedule_selector(MessageWindow::updateNextMessage);
    this->schedule(sel, _delay);
  }
}

VQString* MessageWindow::getCurrentWholeMessage() {
  if (_messageQueue->count() == 0) {
    return VQString::create();
  }
  VQString* vqs = (VQString*)_messageQueue->objectAtIndex(0);
  return vqs;
}

VQString* MessageWindow::getCurrentMessage() {
  return this->getCurrentWholeMessage()->substringWithRange(0, _textIndex);
}

void MessageWindow::setMessageSpeed(int speed) {
  _messageSpeed = speed;
}

void MessageWindow::setOnMessageFinishedFunction(boost::function<void (VQString*, MessageWindow *)> finish) {
  _onFinishedFunction = finish;
}

void MessageWindow::setOnMessageUpdatedFunction(boost::function<void (VQString*, MessageWindow *)> update) {
  _onUpdatedFunction = update;
}

bool MessageWindow::isLastMessage() {
  return _messageQueue->count() <= 1;
}

bool MessageWindow::isEndMessage() {
  return _textIndex >= this->getCurrentWholeMessage()->length();
}

void MessageWindow::setDelay(float d) {
  _delay = d;
}

void MessageWindow::updateNextMessage() {
  _ended = false;
  _textIndex = 0;
  _textTimer = 0;
  _messageQueue->removeObjectAtIndex(0);
  this->unschedule(schedule_selector(MessageWindow::updateNextMessage));
}