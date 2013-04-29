//
//  MessageWindow.h
//  VOXCHRONICLE
//
//  Created by giginet on 2012/10/20.
//
//

#ifndef __VOXCHRONICLE__MessageWindow__
#define __VOXCHRONICLE__MessageWindow__

#include <iostream>
#include "cocos2d.h"
#include <deque>
#include <boost/function.hpp>

#include "VQString.h"

using namespace std;
using namespace cocos2d;
using namespace boost;

class MessageWindow :public CCNode {
 private:
  CCArray* _messageQueue;
  boost::function<void (VQString*, MessageWindow*)> _onFinishedFunction;
  boost::function<void (VQString*, MessageWindow*)> _onUpdatedFunction;
  int _textIndex;
  int _textSpeed;
  float _messageSpeed;
  void onMessageFinished();
  void onMessageUpdated();
  void update(float dt);
  float _delay;
  float _lastDelay;
  void updateNextMessage(CCObject* sender);
  void updateNextText(CCObject* sender);
  bool _ended;
  CCLabelTTF* _label;
  CCLabelTTF* _shadow;
 public:
  MessageWindow(const char* fontName, float size, CCSize dimensions);
  ~MessageWindow();
  void pushMessage(const char* message);
  void setMessageSpeed(float speed);
  void setOnMessageFinishedFunction(function<void (VQString*, MessageWindow*)> finish);
  void setOnMessageUpdatedFunction(function<void (VQString*, MessageWindow*)> update);
  VQString* getCurrentMessage();
  VQString* getCurrentWholeMessage();
  bool isLastMessage();
  bool isEndMessage();
  void setDelay(float d);
  void setLastDelay(float d);
  void start();
  void stop();
  void setTextSpeed(int textSpeed);
  
  /**
   強制的にメッセージを終了させます
   */
  void finishMessage();
};

#endif /* defined(__VOXCHRONICLE__MessageWindow__) */
