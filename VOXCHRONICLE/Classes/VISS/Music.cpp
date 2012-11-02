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
  _tracks = std::vector< std::deque<Track* > >(trackCount);
  _backed = std::deque<bool>(trackCount);
  _willFinish = std::deque<bool>(trackCount);
  for (int i = 0; i < trackCount; ++i) {
    _backed.push_back(false);
    _willFinish.push_back(false);
  }
}

Music::~Music() {
}

Track* Music::getTrack(int trackNumber) {
  return _tracks.at(trackNumber).front();
}

Track* Music::getNextTrack(int trackNumber) {
  return _tracks.at(trackNumber).at(1);
}
  
bool Music::setTrack(const char* fileName, int trackNumber, int index) {
  //Track* next = new Track(fileName);
  Track* next = TrackCache::sharedCache()->addTrack(fileName);
  return setTrack(next, trackNumber, index);
}

bool Music::setTrack(Track* track, int trackNumber, int index) {
  if (trackNumber >= _trackCount) {
    return false;
  }
  _tracks.at(trackNumber).at(index) = track;
  return true;
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
  _tracks.at(trackNumber).push_back(track);
  return track;
}
    
bool Music::play() {
  cocos2d::CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this, -127, false);
  for (std::vector< std::deque< Track* > >::iterator it = _tracks.begin(); it != _tracks.end(); ++it) {
    if (it->size() > 0 && !it->at(0)->play()) {
      return false;
    }
  }
  return true;
}
    
void Music::stop() {
  for (std::vector< std::deque< Track* > >::iterator it = _tracks.begin(); it != _tracks.end(); ++it) {
    for (int j = 0; j < it->size(); ++j) {
      it->at(j)->stop();
      it->at(j)->setVolume(0);
    }
  }
  cocos2d::CCDirector::sharedDirector()->getScheduler()->unscheduleAllSelectorsForTarget(this);
}

void Music::pause() {
  for (std::vector< std::deque< Track* > >::iterator it = _tracks.begin(); it != _tracks.end(); ++it) {
    if (it->size() > 0) {
      it->at(0)->pause();
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
  for (int trackNumber = 0; trackNumber < _trackCount; ++trackNumber) {
    std::deque<Track*>* it = &_tracks.at(trackNumber);
    if (it->size() == 0) continue;
    Track* current = it->front();
    float sub = current->getDuration() - current->getPosition();
    if (!_willFinish.at(trackNumber) && (sub < 0.15 || !current->isPlaying())) {
      //終わりそうなとき
      if (_trackWillFinishFunction != NULL) {
        _trackWillFinishFunction(this, current, NULL, trackNumber);
      }
      _willFinish.at(trackNumber) = true;
      if (it->size() > 1) {
        Track* next = this->getNextTrack(trackNumber);
        next->playAfterTrack(current);
      }
    } else if (!current->isPlaying() && _willFinish.at(trackNumber)) {
      //終わったとき
      it->pop_front();
      current->release();
      _backed.at(trackNumber) = false;
      _willFinish.at(trackNumber) = false;
      if (_trackDidFinishFunction != NULL) {
        if (it->size() == 0) {
          _trackDidFinishFunction(this, current, NULL, trackNumber);
        } else {
          _trackDidFinishFunction(this, current, it->front(), trackNumber);
          if (!it->front()->isPlaying()) {
            it->front()->play();
          }
        }
      }
    } else if (!_backed.at(trackNumber) && current->getDuration() / 2 < current->getPosition()) {
      //裏打ちのとき
      if (_trackDidBackFunction != NULL) {
        _trackDidBackFunction(this, current, trackNumber);
      }
      _backed.at(trackNumber) = true;
    }
  }
}

void Music::removeAllNextTracks() {
  for (int trackNumber = 0; trackNumber < _trackCount; ++trackNumber) {
    std::deque<Track*>* it = &_tracks.at(trackNumber);
    if (it->size() >= 2) it->erase(it->begin() + 1, it->end());
  }
}

bool Music::isLastWillFinishedCall() {
  return static_cast<int>(std::count(_willFinish.begin(), _willFinish.end(), true)) == _trackCount - 1;
}