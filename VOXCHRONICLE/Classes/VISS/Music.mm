//
//  Music.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/8/31.
//
//

#include "Music.h"

using namespace VISS;

VISS::Music::Music() {
  Music(0);
}

VISS::Music::Music(int trackCount) {
  _trackCount = trackCount;
  _tracks = std::vector< std::deque<boost::shared_ptr<Track> > >(trackCount);
}

VISS::Music::~Music() {
}

boost::shared_ptr<VISS::Track> VISS::Music::getTrack(int trackNumber) {
  return _tracks.at(trackNumber).front();
}

boost::shared_ptr<VISS::Track> VISS::Music::getNextTrack(int trackNumber) {
  return _tracks.at(trackNumber).at(1);
}
  
bool VISS::Music::setTrack(const std::string* fileName, int trackNumber, int index) {
  Track* next = new Track(fileName);
  return setTrack(next, trackNumber, index);
}

bool VISS::Music::setTrack(Track* track, int trackNumber, int index) {
  if (trackNumber >= _trackCount) {
    return false;
  }
  _tracks.at(trackNumber).at(index) = boost::shared_ptr<Track>(track);
  return true;
}

bool VISS::Music::pushTrack(const std::string* fileName, int trackNumber) {
  return pushTrack(fileName, trackNumber, 1);
}

bool VISS::Music::pushTrack(const std::string* fileName, int trackNumber, int repeat) {
  for (int i = 0; i < repeat; ++i) {
    Track* next = new Track(fileName);
    bool result = pushTrack(next, trackNumber);
    if (!result) {
      return false;
    }
  }
  return true;
}

bool VISS::Music::pushTrack(Track* track, int trackNumber) {
  if (trackNumber >= _trackCount) {
    return false;
  }
  _tracks.at(trackNumber).push_back(boost::shared_ptr<Track>(track));
  return true;
}
    
bool VISS::Music::play() {
  cocos2d::CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this, -127, false);
  for (std::vector< std::deque< boost::shared_ptr<Track> > >::iterator it = _tracks.begin(); it != _tracks.end(); ++it) {
    if (it->size() > 0 && !it->at(0)->play()) {
      return false;
    }
  }
  return true;
}
    
void VISS::Music::stop() {
  for (std::vector< std::deque< boost::shared_ptr<Track> > >::iterator it = _tracks.begin(); it != _tracks.end(); ++it) {
    if (it->size() > 0) {
      it->at(0)->stop();
    }
  }
  cocos2d::CCDirector::sharedDirector()->getScheduler()->unscheduleAllSelectorsForTarget(this);
}

void VISS::Music::pause() {
  for (std::vector< std::deque< boost::shared_ptr<Track> > >::iterator it = _tracks.begin(); it != _tracks.end(); ++it) {
    if (it->size() > 0) {
      it->at(0)->pause();
    }
  }
  cocos2d::CCDirector::sharedDirector()->getScheduler()->unscheduleAllSelectorsForTarget(this);
}

void VISS::Music::update(float dt) {
  for (int i = 0; i < _trackCount; ++i) {
    std::deque< boost::shared_ptr<Track> >* it = &_tracks.at(i);
    boost::shared_ptr<VISS::Track> current = it->front();
    float sub = current->getDuration() - current->getPosition();
    if (it->size() > 1 && sub <= current->getDuration() * 0.1) {
      it->pop_front();
      if (sub - dt / 2.0 > 0) {
        it->front()->playAfterTime(sub - dt / 2.0);
      } else {
        it->front()->play();
      }
    }
  }
}