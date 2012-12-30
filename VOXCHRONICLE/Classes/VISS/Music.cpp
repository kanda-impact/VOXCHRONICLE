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
  _tracks = std::vector< CCArray* >(trackCount);
  for (int i = 0; i < _trackCount; ++i) {
    _tracks[i] = CCArray::create();
    _tracks[i]->retain();
  }
}

Music::~Music() {
}

Track* Music::getTrack(int trackNumber) {
  return (Track*)_tracks.at(trackNumber)->objectAtIndex(0);
}

Track* Music::getNextTrack(int trackNumber) {
  if (_tracks.at(trackNumber)->count() > 1) {
    return (Track*)_tracks.at(trackNumber)->objectAtIndex(1);
  }
  return NULL;
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
  _tracks.at(trackNumber)->replaceObjectAtIndex(index, track);
  return track;
}

Track* Music::pushTrack(const char* fileName, int trackNumber) {
  return pushTrack(fileName, trackNumber, 1);
}

Track* Music::pushTrack(const char* fileName, int trackNumber, int repeat) {
  Track* next;
  for (int i = 0; i < repeat; ++i) {
    next = TrackCache::sharedCache()->addTrack(fileName);
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
  _tracks.at(trackNumber)->addObject(track);
  return track;
}
    
bool Music::play() {
  cocos2d::CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this, -127, false);
  for (std::vector< CCArray* >::iterator it = _tracks.begin(); it != _tracks.end(); ++it) {
    if ((*it)->count() > 0 && !((Track*)(*it)->objectAtIndex(0))->play()) {
      return false;
    }
  }
  this->setScheduleForMain();
  return true;
}
    
void Music::stop() {
  for (std::vector< CCArray* >::iterator it = _tracks.begin(); it != _tracks.end(); ++it) {
    for (int j = 0; j < (*it)->count(); ++j) {
      ((Track*)(*it)->objectAtIndex(j))->stop();
      ((Track*)(*it)->objectAtIndex(j))->setVolume(0);
    }
  }
  cocos2d::CCDirector::sharedDirector()->getScheduler()->unscheduleAllSelectorsForTarget(this);
}

void Music::pause() {
  for (std::vector< CCArray* >::iterator it = _tracks.begin(); it != _tracks.end(); ++it) {
    if ((*it)->count() > 0) {
      ((Track*)(*it)->objectAtIndex(0))->pause();
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
    CCArray* it = _tracks.at(trackNumber);
    if (it->count() >= 2) {
      for (int i = 1; i < it->count(); ++i) {
        it->removeObjectAtIndex(i);
      }
    }
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
    CCArray* channel = _tracks[trackNumber];
    Track* current = (Track*)channel->objectAtIndex(0);
    channel->removeObjectAtIndex(0);
    current->release();
  }
  this->setScheduleDelay(0.0f);
}

void Music::onTrackDidBack() {
  if (_trackDidBackFunction != NULL) {
    _trackDidBackFunction(this, this->getCurrentMainTrack(), 0);
  }
}

Track* Music::getCurrentMainTrack() {
  CCArray* channel = _tracks[0];
  return (Track*)channel->objectAtIndex(0);
}

void Music::setScheduleForMain() {
  this->setSchedule(this->getCurrentMainTrack());
}

void Music::setSchedule(VISS::Track *track) {
  CCScheduler* scheduler = CCDirector::sharedDirector()->getScheduler();
  scheduler->scheduleSelector((SEL_SCHEDULE)&Music::onTrackDidBack, this, track->getDuration() / 2.0f, false, 0, 0);
  scheduler->scheduleSelector((SEL_SCHEDULE)&Music::onTrackWillFinish, this, track->getDuration() * 0.8f, false, 0, 0);
  scheduler->scheduleSelector((SEL_SCHEDULE)&Music::onTrackDidFinish, this, track->getDuration() * 0.98f, false, 0, 0);
}

void Music::setScheduleDelay(float delay) {
  CCScheduler* scheduler = CCDirector::sharedDirector()->getScheduler();
  scheduler->scheduleSelector((SEL_SCHEDULE)&Music::setScheduleForMain, this, delay, false, 0, 0);
}