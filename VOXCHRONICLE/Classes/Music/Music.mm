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
  _tracks = std::vector< boost::shared_ptr<Track> >(trackCount);
  _nextTracks = std::vector< boost::shared_ptr<Track> >(trackCount);
}

VISS::Music::~Music() {
}

boost::shared_ptr<VISS::Track> VISS::Music::getTrack(int trackNumber) {
  return _tracks.at(trackNumber);
}

bool VISS::Music::setTrack(const std::string* fileName, int trackNumber) {
  Track* next = new Track(fileName);
  return setTrack(next, trackNumber);
}

bool VISS::Music::setTrack(Track* track, int trackNumber) {
  if (trackNumber >= _trackCount) {
    return false;
  }
  _tracks.at(trackNumber) = boost::shared_ptr<Track>(track);
  return true;
}

bool VISS::Music::setNextTrack(const std::string* fileName, int trackNumber) {
  Track* next = new Track(fileName);
  return setNextTrack(next, trackNumber);
}

bool VISS::Music::setNextTrack(Track* track, int trackNumber) {
  if (trackNumber >= _trackCount) {
    return false;
  }
  _nextTracks.at(trackNumber) = boost::shared_ptr<Track>(track);
  return true;
}
    
bool VISS::Music::play() {
  cocos2d::SEL_SCHEDULE selector = (cocos2d::SEL_SCHEDULE)&Music::update;
  cocos2d::CCDirector::sharedDirector()->getScheduler()->scheduleSelector(selector, this, 0.01, false, -1, 0);
  for (std::vector<boost::shared_ptr<Track> >::iterator it = _tracks.begin(); it != _tracks.end(); ++it) {
    if (!(*it)->play()) {
      return false;
    }
  }
  return true;
}
    
void VISS::Music::stop() {
  for (std::vector<boost::shared_ptr<Track> >::iterator it = _tracks.begin(); it != _tracks.end(); ++it) {
    (*it)->stop();
  }
  cocos2d::CCDirector::sharedDirector()->getScheduler()->unscheduleAllSelectorsForTarget(this);
}

void VISS::Music::pause() {
  for (std::vector<boost::shared_ptr<Track> >::iterator it = _tracks.begin(); it != _tracks.end(); ++it) {
    (*it)->pause();
  }
  cocos2d::CCDirector::sharedDirector()->getScheduler()->unscheduleAllSelectorsForTarget(this);
}

void VISS::Music::update(float dt) {
  for (int i = 0; i < _trackCount; ++i) {
    boost::shared_ptr<Track> it = _tracks.at(i);
    if (!it->isPlaying() && _nextTracks.at(i)) {
      _tracks.at(i) = _nextTracks.at(i);
      _nextTracks.at(i)->play();
    }
  }
}