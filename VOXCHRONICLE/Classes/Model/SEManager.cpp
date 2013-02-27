//
//  SEManager.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/2/27.
//
//

#include "SEManager.h"
#include "SimpleAudioEngine.h"

static SEManager* _shared = NULL;

using namespace cocos2d;

SEManager* SEManager::sharedManager () {
  if (!_shared) {
    _shared = new SEManager();
  }
  return _shared;
}

SEManager::SEManager() {
  _seQueue = CCArray::create();
  _seQueue->retain();
  CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(SEManager::playEffect), this, 0.03f, false);
}

SEManager::~SEManager() {
  _seQueue->release();
}

void SEManager::registerEffect(const char *filename) {
  CCString* str = CCString::create(filename);
  _seQueue->addObject(str);
}

void SEManager::playEffect(CCObject *sender) {
  if (_seQueue->count() > 0) {
    CCString* str = (CCString*)_seQueue->objectAtIndex(0);
    const char* filename = str->getCString();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(filename);
    _seQueue->removeObjectAtIndex(0);
  }
}