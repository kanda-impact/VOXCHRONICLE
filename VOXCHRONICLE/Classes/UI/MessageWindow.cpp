//
//  MessageWindow.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/10/20.
//
//

#include "MessageWindow.h"
#include <sstream>

const int kDefaultMessageWindowDelay = 1.5f;
const int kDefalutMessageWindowLastDelay = 3.0f;
const int kDefaultMessageWindowSpeed = 0.3f;

MessageWindow::MessageWindow(const char* fontName, float size, CCSize dimensions) {
  _messageQueue = CCArray::create();
  _messageQueue->retain();
  _textIndex = 0;
  _delay = kDefaultMessageWindowDelay;
  _lastDelay = kDefalutMessageWindowLastDelay;
  _messageSpeed = kDefaultMessageWindowSpeed;
  _label = CCLabelTTF::create("", fontName, size, dimensions, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
  _label->retain();
  _label->setColor(ccc3(255, 255, 255));
  this->addChild(_label);
  _onFinishedFunction = NULL;
  _onUpdatedFunction = NULL;
  _ended = false;
  this->schedule(schedule_selector(MessageWindow::updateNextText), _messageSpeed);
}

MessageWindow::~MessageWindow() {
  _messageQueue->release();
  _label->release();
}

void MessageWindow::pushMessage(const char* message) {
  VQString* str = VQString::create(message);
  if (str->length() == 0) return;
  if (this->isLastMessage() && this->isEndMessage()) { // 最後のメッセージで終わってたら
    this->unschedule(schedule_selector(MessageWindow::updateNextMessage));
    _messageQueue->addObject(str);
    this->updateNextMessage(NULL); // 強制的に次のメッセージに送ってやる
  } else {
    _messageQueue->addObject(str);
  }
}

void MessageWindow::update(float dt) {

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
  this->unschedule(schedule_selector(MessageWindow::updateNextText));
  this->schedule(schedule_selector(MessageWindow::updateNextText), _messageSpeed);
}

void MessageWindow::setOnMessageFinishedFunction(boost::function<void (VQString*, MessageWindow *)> finish) {
  _onFinishedFunction = finish;
}

void MessageWindow::setOnMessageUpdatedFunction(boost::function<void (VQString*, MessageWindow *)> update) {
  _onUpdatedFunction = update;
}

bool MessageWindow::isLastMessage() {
  return _messageQueue->count() == 1;
}

bool MessageWindow::isEndMessage() {
  return _textIndex >= this->getCurrentWholeMessage()->length();
}

void MessageWindow::setDelay(float d) {
  _delay = d;
}

void MessageWindow::setLastDelay(float d) {
  _lastDelay = d;
}

void MessageWindow::updateNextText(CCObject* sender) {
  _label->setString(this->getCurrentMessage()->getCString());
  if (_messageQueue->count() == 0) return;
  if (this->isEndMessage()) return;
  if (_messageQueue->count() > 0 && _textIndex < this->getCurrentWholeMessage()->length()) {
    if (_onUpdatedFunction) {
      _onUpdatedFunction(this->getCurrentWholeMessage()->substringWithRange(_textIndex, 1), this);
    }
    _textIndex += 1;
    // メッセージが終わったら、次のメッセージに
    if (!_ended && _textIndex > this->getCurrentWholeMessage()->length() - 1) {
      _ended = true;
      _textIndex = this->getCurrentWholeMessage()->length() - 1;
      if (_onFinishedFunction) {
        _onFinishedFunction(this->getCurrentWholeMessage(), this);
      }
      SEL_SCHEDULE sel = (SEL_SCHEDULE)schedule_selector(MessageWindow::updateNextMessage);
      this->scheduleOnce(sel, this->isLastMessage() ? _lastDelay : _delay);
    }
  }
}

void MessageWindow::updateNextMessage(CCObject* sender) {
  _ended = false;
  _textIndex = 0;
  _messageQueue->removeObjectAtIndex(0);
  this->unschedule(schedule_selector(MessageWindow::updateNextMessage));
}