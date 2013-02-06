//
//  MessageManager.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/2/6.
//
//

#include "MessageManager.h"
#include "LuaObject.h"

MessageManager* MessageManager::_instance = NULL;

MessageManager* MessageManager::sharedManager() {
  if (!_instance) _instance = new MessageManager();
  return _instance;
}

MessageManager::MessageManager() {
  _defaultWindow = NULL;
}

MessageManager::~MessageManager() {
  if (_defaultWindow) {
    _defaultWindow->release();
  }
}

void MessageManager::setDefaultMessageWindow(MessageWindow *window) {
  if (_defaultWindow) {
    _defaultWindow->release();
  }
  _defaultWindow = window;
  if (window) {
    window->retain();
  }
}

void MessageManager::pushMessage(const char *message) {
  if (_defaultWindow) {
    _defaultWindow->pushMessage(message);
  }
}

void MessageManager::pushRandomMessageFromLua(const char *luaName) {
  LuaObject* obj = new LuaObject(luaName);
  CCLuaValueArray* array = obj->getArray("Messages");
  CCArray* messages = CCArray::create();
  for (CCLuaValueArrayIterator it = array->begin(); it != array->end(); ++it) {
    CCString* str = CCString::create(it->stringValue());
    messages->addObject(str);
  }
  CCString* random = (CCString*)messages->randomObject();
  this->pushMessage(random->getCString());
}