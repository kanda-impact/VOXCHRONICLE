//
//  MessageWindow.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/10/20.
//
//

#include "MessageWindow.h"

MessageWindow::MessageWindow(const char* fontName, int size) {
  _messageQueue = new deque<string>();
  _textIndex = 0;
  _textTimer = 0;
  _delay = 1.0;
  _messageSpeed = 0.5;
  CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this, -1, false);
  _label = CCLabelTTF::create("", fontName, size);
  _label->retain();
  _label->setColor(ccc3(255, 255, 255));
  this->addChild(_label);
  _onFinishedFunction = NULL;
  _onUpdatedFunction = NULL;
  _ended = false;
}

MessageWindow::~MessageWindow() {
  delete _messageQueue;
  _label->release();
}

void MessageWindow::pushMessage(string message) {
  _messageQueue->push_back(message);
}

void MessageWindow::update(float dt) {
  _label->setString(this->getCurrentMessage().c_str());
  if (_messageQueue->size() == 0) return;
  if (this->isEndMessage()) return;
  if (_textIndex <= this->getCurrentWholeMessage().length() - 1) {
    _textTimer += _messageSpeed;
  }
  int updated = floor(_textTimer);
  if (updated >= 1) {
    if (_onUpdatedFunction) {
      _onUpdatedFunction(this->getCurrentWholeMessage().substr(_textIndex, updated), this);
    }
    _textTimer -= updated;
    _textIndex += updated;
  }
  if (!_ended && _textIndex > this->getCurrentWholeMessage().length() - 1) {
    _ended = true;
    _textIndex = this->getCurrentWholeMessage().length() - 1;
    if (_onFinishedFunction) {
      _onFinishedFunction(this->getCurrentWholeMessage(), this);
    }
    SEL_SCHEDULE sel = (SEL_SCHEDULE)schedule_selector(MessageWindow::updateNextMessage);
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(sel, this, _delay, false, 1, 0);
  }
}

string MessageWindow::getCurrentWholeMessage() {
  if (_messageQueue->size() == 0) {
    return "";
  }
  return _messageQueue->front();
}

string MessageWindow::getCurrentMessage() {
  return this->getCurrentWholeMessage().substr(0, _textIndex);
}

void MessageWindow::setMessageSpeed(int speed) {
  _messageSpeed = speed;
}

void MessageWindow::setOnMessageFinishedFunction(function<void (string, MessageWindow *)> finish) {
  _onFinishedFunction = finish;
}

void MessageWindow::setOnMessageUpdatedFunction(function<void (string, MessageWindow *)> update) {
  _onUpdatedFunction = update;
}

bool MessageWindow::isLastMessage() {
  return _messageQueue->size() <= 1;
}

bool MessageWindow::isEndMessage() {
  return _textIndex >= this->getCurrentWholeMessage().length();
}

void MessageWindow::setDelay(float d) {
  _delay = d;
}

void MessageWindow::updateNextMessage() {
  _ended = false;
  _textIndex = 0;
  _textTimer = 0;
  _messageQueue->pop_front();
  CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(MessageWindow::updateNextMessage), this);
}