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
#include <deque.h>
#include <boost/function.hpp>

using namespace std;
using namespace cocos2d;
using namespace boost;

class MessageWindow :public CCNode {
 private:
  deque<string>* _messageQueue;
  function<void (string, MessageWindow*)> _onFinishedFunction;
  function<void (string, MessageWindow*)> _onUpdatedFunction;
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
  MessageWindow(const char* fontName, int size);
  ~MessageWindow();
  void pushMessage(string message);
  void setMessageSpeed(int speed);
  void setOnMessageFinishedFunction(function<void (string, MessageWindow*)> finish);
  void setOnMessageUpdatedFunction(function<void (string, MessageWindow*)> update);
  string getCurrentMessage();
  string getCurrentWholeMessage();
  bool isLastMessage();
  bool isEndMessage();
  void setDelay(float d);
};

#endif /* defined(__VOXCHRONICLE__MessageWindow__) */
