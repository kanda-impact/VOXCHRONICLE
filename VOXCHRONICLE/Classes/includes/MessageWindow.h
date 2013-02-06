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
  float _textTimer;
  float _messageSpeed;
  void onMessageFinished();
  void onMessageUpdated();
  void update(float dt);
  float _delay;
  void updateNextMessage();
  bool _ended;
  CCLabelTTF* _label;
 public:
  MessageWindow(const char* fontName, float size, CCSize dimensions);
  ~MessageWindow();
  void pushMessage(const char* message);
  void setMessageSpeed(int speed);
  void setOnMessageFinishedFunction(function<void (VQString*, MessageWindow*)> finish);
  void setOnMessageUpdatedFunction(function<void (VQString*, MessageWindow*)> update);
  VQString* getCurrentMessage();
  VQString* getCurrentWholeMessage();
  bool isLastMessage();
  bool isEndMessage();
  void setDelay(float d);
};

#endif /* defined(__VOXCHRONICLE__MessageWindow__) */
