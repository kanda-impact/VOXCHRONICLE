//
//  Music.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/8/31.
//
//

#include <algorithm>
#include <sstream>
#include "macros.h"
#include "Music.h"
#include "TrackCache.h"

using namespace VISS;

Music::Music() {
  Music(0);
}

Music::Music(int trackCount) {
  _trackCount = trackCount;
  _tracks = std::vector< std::deque<Track* >* >(trackCount);
  for (int i = 0; i < _trackCount; ++i) {
    _tracks[i] = new std::deque<Track*>();
  }
}

Music::~Music() {
}

Track* Music::getTrack(int trackNumber) {
  return _tracks.at(trackNumber)->front();
}

Track* Music::getNextTrack(int trackNumber) {
  return _tracks.at(trackNumber)->at(1);
}
  
Track* Music::setTrack(const char* fileName, int trackNumber, int index) {
  //Track* next = new Track(fileName);
  Track* next = TrackCache::sharedCache()->addTrack(fileName);
  return setTrack(next, trackNumber, index);
}

Track* Music::setTrack(Track* track, int trackNumber, int index) {
  if (trackNumber >= _trackCount) {
    return NULL;
  }
  _tracks.at(trackNumber)->at(index) = track;
  return track;
}

Track* Music::pushTrack(const char* fileName, int trackNumber) {
  return pushTrack(fileName, trackNumber, 1);
}

Track* Music::pushTrack(const char* fileName, int trackNumber, int repeat) {
  Track* next;
  for (int i = 0; i < repeat; ++i) {
    next = new Track(fileName);
    bool result = pushTrack(next, trackNumber);
    if (!result) {
      return NULL;
    }
  }
  return next;
}

Track* Music::pushTrack(Track* track, int trackNumber) {
  if (trackNumber >= _trackCount) {
    return NULL;
  }
  _tracks.at(trackNumber)->push_back(track);
  return track;
}
    
bool Music::play() {
  cocos2d::CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this, -127, false);
  for (std::vector< std::deque< Track* >* >::iterator it = _tracks.begin(); it != _tracks.end(); ++it) {
    if ((*it)->size() > 0 && !(*it)->at(0)->play()) {
      return false;
    }
  }
  this->setScheduleForMain();
  return true;
}
    
void Music::stop() {
  for (std::vector< std::deque< Track* >* >::iterator it = _tracks.begin(); it != _tracks.end(); ++it) {
    for (int j = 0; j < (*it)->size(); ++j) {
      (*it)->at(j)->stop();
      (*it)->at(j)->setVolume(0);
    }
  }
  cocos2d::CCDirector::sharedDirector()->getScheduler()->unscheduleAllSelectorsForTarget(this);
}

void Music::pause() {
  for (std::vector< std::deque< Track* >* >::iterator it = _tracks.begin(); it != _tracks.end(); ++it) {
    if ((*it)->size() > 0) {
      (*it)->at(0)->pause();
    }
  }
  cocos2d::CCDirector::sharedDirector()->getScheduler()->unscheduleAllSelectorsForTarget(this);
}

void Music::setTrackDidBackFunction(boost::function<void (Music *, Track *, int)> f) {
  _trackDidBackFunction = f;
}

void Music::setTrackWillFinishFunction(boost::function<void (Music *, Track *, Track *, int)> f) {
  _trackWillFinishFunction = f;
}

void Music::setTrackDidFinishFunction(boost::function<void (Music *, Track *, Track *, int)> f) {
  _trackDidFinishFunction = f;
}

void VISS::Music::update(float dt) {
}

void Music::removeAllNextTracks() {
  for (int trackNumber = 0; trackNumber < _trackCount; ++trackNumber) {
    std::deque<Track*>* it = _tracks.at(trackNumber);
    if (it->size() >= 2) it->erase(it->begin() + 1, it->end());
  }
}

void Music::onTrackWillFinish() {
  //終わりそうなとき
  if (_trackWillFinishFunction != NULL) {
    _trackWillFinishFunction(this, this->getCurrentMainTrack(), NULL, 0);
  }
  for (int trackNumber = 0; trackNumber < _trackCount; ++trackNumber) {
    Track* next = this->getNextTrack(trackNumber);
    if (next) {
      next->playAfterTime(this->getCurrentMainTrack()->getDuration() * 0.1f);
    }
  }
  
}

void Music::onTrackDidFinish() {
  if (_trackDidFinishFunction != NULL) {
    _trackDidFinishFunction(this, this->getCurrentMainTrack(), NULL, 0);
  }
  for (int trackNumber = 0; trackNumber < _trackCount; ++trackNumber) {
    std::deque<Track*>* channel = _tracks[trackNumber];
    channel->pop_front();
  }
  this->setScheduleDelay(0.0f);
}

void Music::onTrackDidBack() {
  if (_trackDidBackFunction != NULL) {
    _trackDidBackFunction(this, this->getCurrentMainTrack(), 0);
  }
}

Track* Music::getCurrentMainTrack() {
  std::deque<Track*>* channel = _tracks[0];
  return channel->at(0);
}

void Music::setScheduleForMain() {
  this->setSchedule(this->getCurrentMainTrack());
}

void Music::setSchedule(VISS::Track *track) {
  CCScheduler* scheduler = CCDirector::sharedDirector()->getScheduler();
  scheduler->scheduleSelector((SEL_SCHEDULE)&Music::onTrackDidBack, this, track->getDuration() / 2.0f, false, 0, 0);
  scheduler->scheduleSelector((SEL_SCHEDULE)&Music::onTrackWillFinish, this, track->getDuration() * 0.9f, false, 0, 0);
  scheduler->scheduleSelector((SEL_SCHEDULE)&Music::onTrackDidFinish, this, track->getDuration(), false, 0, 0);
}

void Music::setScheduleDelay(float delay) {
  CCScheduler* scheduler = CCDirector::sharedDirector()->getScheduler();
  scheduler->scheduleSelector((SEL_SCHEDULE)&Music::setScheduleForMain, this, delay, false, 0, 0);
}