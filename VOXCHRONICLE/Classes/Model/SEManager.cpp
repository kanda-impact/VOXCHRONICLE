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

const float kSEManagerDefaultDelay = 0.03f;

SEManager* SEManager::sharedManager () {
  if (!_shared) {
    _shared = new SEManager();
  }
  return _shared;
}

SEManager::SEManager() {
  _seQueue = new queue< pair<string, float> >();
  _currentDelay = 0;
  CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this, 0, false);
}

SEManager::~SEManager() {
  delete _seQueue;
}

void SEManager::update(float delay) {
  if (!_seQueue->empty()) {
    _currentDelay += delay;
    this->playEffect();
  }
}


void SEManager::registerEffect(const char *filename, float delay) {
  pair<string, float> p;
  p.first = string(filename);
  p.second = delay;
  _seQueue->push(p);
}

void SEManager::registerEffect(const char *filename) {
  this->registerEffect(filename, kSEManagerDefaultDelay);
}

void SEManager::playEffect() {
  if (!_seQueue->empty()) {
    pair<string, float> p = _seQueue->front();
    if (p.second < _currentDelay) {
      CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(p.first.c_str());
      _seQueue->pop();
      _currentDelay = 0;
    }
  }
}