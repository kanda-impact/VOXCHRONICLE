//
//  Track.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/8/31.
//
//

#include "Track.h"
#include "ObjectAL.h"

// It is wrapper class for ObjectAL::OALAudioTrack.

struct VISS::Track::AudioTrack {
  OALAudioTrack* track;
};

VISS::Track::Track(const std::string* fileName) : _track(new VISS::Track::AudioTrack) {
  NSString* file = [NSString stringWithUTF8String:fileName->c_str()];
  _track->track = [[OALAudioTrack alloc] init];
  [_track->track preloadFile:file];
}

VISS::Track::~Track() {
  [_track->track release];
}

bool VISS::Track::play() {
  return [_track->track play];
}

void VISS::Track::playAfterTime(float time) {
  float dt = _track->track.deviceCurrentTime;
  [_track->track playAtTime:dt + time];
}
  
void VISS::Track::stop() {
  return [_track->track stop];
}
  
void VISS::Track::pause() {
  _track->track.paused = YES;
}

bool VISS::Track::isPlaying() {
  return _track->track.playing;
}

float VISS::Track::getDuration() {
  return _track->track.duration;
}

float VISS::Track::getPosition() {
  return _track->track.currentTime;
}