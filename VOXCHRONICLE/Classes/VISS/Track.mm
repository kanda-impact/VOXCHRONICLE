//
//  Track.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/8/31.
//
//

#include "Track.h"
#include "ObjectAL.h"
#include "BufferCache.h"
#include "Buffer.h"

// It is wrapper class for ObjectAL::OALAudioTrack.

using namespace std;
using namespace VISS;

struct Buffer::BufferWrapper {
  ALBuffer* buffer;
};

struct Track::AudioTrack {
  ALBuffer* buffer;
  ALSource* source;
};

Track::Track(const char* fileName) : _track(new VISS::Track::AudioTrack) {
  _fileName = string(fileName);
  
  _track->source = [[ALSource source] retain];
  
  // Preload the buffers so we don't have to load and play them later.
  Buffer* buffer = BufferCache::sharedCache()->addBuffer(fileName);
  Buffer::BufferWrapper* wrapper = buffer->getBuffer();
  _track->buffer = wrapper->buffer;
}

Track::~Track() {
  //[_track->buffer release];
  [_track->source release];
}

bool Track::play() {
  if (_track && _track->source) {
    [_track->source play:_track->buffer];
  }
  return true;
}

void Track::playAfterTime(float time) {
  CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(Track::play), this, time, false, 0, 0);
}

void Track::stop() {
  return [_track->source stop];
}
  
void Track::pause() {
  _track->source.paused = YES;
}

void Track::resume() {
  _track->source.paused = NO;
}

bool Track::isPlaying() {
  return _track->source.playing;
}

float Track::getDuration() {
  return _track->buffer.duration;
}

float Track::getPosition() {
  return _track->source.offsetInSeconds;
}

/*float Track::getDeviceCurrentTime() {
  
  //return _track->track.deviceCurrentTime;
}*/

void Track::setVolume(float v) {
  [_track->source setVolume:v];
}

void Track::playAfterTrack(VISS::Track *track) {
  NSTimeInterval trackTimeRemaining = track->getDuration() - track->getPosition();
  track->playAfterTime(trackTimeRemaining);
}

string Track::getTrackName() {
  return string(_fileName);
}