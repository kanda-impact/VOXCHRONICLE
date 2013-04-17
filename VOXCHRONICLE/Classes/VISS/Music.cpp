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

using namespace VISS;

Music::Music() {
  Music(0);
}

Music::Music(int trackCount) {
  _trackCount = trackCount;
  _measureCount = 0;
  _tracks = CCArray::create();
  _tracks->retain();
  for (int i = 0; i < _trackCount; ++i) {
    _tracks->addObject(CCArray::create());
  }
}

Music::~Music() {
  _tracks->release();
}

Track* Music::getTrack(int trackNumber) {
  return (Track*)((CCArray*)_tracks->objectAtIndex(trackNumber))->objectAtIndex(0);
}

Track* Music::getNextTrack(int trackNumber) {
  if (((CCArray*)_tracks->objectAtIndex(trackNumber))->count() > 1) {
    return (Track*)((CCArray*)_tracks->objectAtIndex(trackNumber))->objectAtIndex(1);
  }
  return NULL;
}

Track* Music::setTrack(const char* fileName, int trackNumber, int index) {
  //Track* next = new Track(fileName);
  Track* next = new Track(fileName);
  next->autorelease();
  return setTrack(next, trackNumber, index);
}

Track* Music::setTrack(Track* track, int trackNumber, int index) {
  if (trackNumber >= _trackCount) {
    return NULL;
  }
  ((CCArray*)_tracks->objectAtIndex(trackNumber))->replaceObjectAtIndex(index, track);
  return track;
}

Track* Music::pushTrack(const char* fileName, int trackNumber) {
  return pushTrack(fileName, trackNumber, 1);
}

Track* Music::pushTrack(const char* fileName, int trackNumber, int repeat) {
  Track* next = new Track(fileName);
  next->autorelease();
  for (int i = 0; i < repeat; ++i) {
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
  ((CCArray*)_tracks->objectAtIndex(trackNumber))->addObject(track);
  return track;
}

bool Music::play() {
  CCScheduler* scheduler = cocos2d::CCDirector::sharedDirector()->getScheduler();
  if (scheduler->isTargetPaused(this)) {
    // 再生再開
    CCObject* obj = NULL;
    CCARRAY_FOREACH(_tracks, obj) {
      CCArray* track = (CCArray*)obj;
      if (track->count() > 0) {
        Track* t = (Track*)((CCArray*)track->objectAtIndex(0));
        t->resume();
      }
    }
    scheduler->resumeTarget(this);
  } else {
    // 初再生
    CCObject* obj = NULL;
    CCARRAY_FOREACH(_tracks, obj) {
      CCArray* track = (CCArray*)obj;
      if (track->count() > 0 && !((Track*)((CCArray*)track->objectAtIndex(0)))->play()) {
        return false;
      }
    }
    cocos2d::CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this, -127, false);
    this->setScheduleForMain();
  }
  return true;
}

void Music::stop() {
  // 先の含め全部止める
  CCObject* obj = NULL;
  CCARRAY_FOREACH(_tracks, obj) {
    CCArray* track = (CCArray*)obj;
    CCObject* obj2 = NULL;
    CCARRAY_FOREACH(track, obj2) {
      Track* t = (Track*)obj2;
      t->stop();
      t->setVolume(0);
    }
  }
  cocos2d::CCDirector::sharedDirector()->getScheduler()->unscheduleAllSelectorsForTarget(this);
}

void Music::pause() {
  CCObject* obj = NULL;
  CCARRAY_FOREACH(_tracks, obj) {
    CCArray* track = (CCArray*)obj;
    if (track->count() > 0) {
      Track* t = (Track*)((CCArray*)track->objectAtIndex(0));
      t->pause();
    }
  }
  cocos2d::CCDirector::sharedDirector()->getScheduler()->pauseTarget(this);
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
    CCArray* track = (CCArray*)_tracks->objectAtIndex(trackNumber);
    if (track->count() >= 2) {
      for (int i = 1; i < track->count(); ++i) {
        track->removeObjectAtIndex(i);
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
      next->playAfterTime(this->getCurrentMainTrack()->getDuration() * 0.15f);
    }
  }
  
}

void Music::onTrackDidFinish() {
  if (_trackDidFinishFunction != NULL) {
    _trackDidFinishFunction(this, this->getCurrentMainTrack(), NULL, 0);
  }
  for (int trackNumber = 0; trackNumber < _trackCount; ++trackNumber) {
    CCArray* channel = (CCArray*)_tracks->objectAtIndex(trackNumber);
    channel->removeObjectAtIndex(0);
    ++_measureCount;
  }
  this->setScheduleDelay(0.0f);
}

void Music::onTrackDidBack() {
  if (_trackDidBackFunction != NULL) {
    _trackDidBackFunction(this, this->getCurrentMainTrack(), 0);
  }
}

Track* Music::getCurrentMainTrack() {
  CCArray* channel = (CCArray*)_tracks->objectAtIndex(0);
  return (Track*)channel->objectAtIndex(0);
}

void Music::setScheduleForMain() {
  this->setSchedule(this->getCurrentMainTrack());
}

void Music::setSchedule(VISS::Track *track) {
  CCScheduler* scheduler = CCDirector::sharedDirector()->getScheduler();
  scheduler->scheduleSelector(schedule_selector(Music::onTrackDidBack), this, track->getDuration() / 2.0f, false, 0, 0);
  scheduler->scheduleSelector(schedule_selector(Music::onTrackWillFinish), this, track->getDuration() * 0.85f, false, 0, 0);
  scheduler->scheduleSelector(schedule_selector(Music::onTrackDidFinish), this, track->getDuration() - 0.02f, false, 0, 0);
}

void Music::setScheduleDelay(float delay) {
  CCScheduler* scheduler = CCDirector::sharedDirector()->getScheduler();
  scheduler->scheduleSelector((SEL_SCHEDULE)&Music::setScheduleForMain, this, delay, false, 0, 0);
}