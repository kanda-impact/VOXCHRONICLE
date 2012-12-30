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

using namespace std;
using namespace VISS;

struct Track::AudioTrack {
  OALAudioTrack* track;
};

Track::Track(const char* fileName) : _track(new VISS::Track::AudioTrack) {
  NSString* file = [NSString stringWithUTF8String:fileName];
  _fileName = string(fileName);
  _track->track = [[OALAudioTrack alloc] init];
  [_track->track preloadFileAsync:file target:NULL selector:NULL];
}

Track::~Track() {
  [_track->track release];
}

bool Track::play() {
  [_track->track play];
  return true;
}

void Track::playAfterTime(float time) {
  float dt = _track->track.deviceCurrentTime;
  [_track->track playAtTime:dt + time];
}
  
void Track::stop() {
  return [_track->track stop];
}
  
void Track::pause() {
  _track->track.paused = YES;
}

bool Track::isPlaying() {
  return _track->track.playing;
}

float Track::getDuration() {
  return _track->track.duration;
}

float Track::getPosition() {
  return _track->track.currentTime;
}

float Track::getDeviceCurrentTime() {
  return _track->track.deviceCurrentTime;
}

void Track::setVolume(float v) {
  [_track->track setVolume:v];
}

void Track::playAfterTrack(VISS::Track *track) {
  NSTimeInterval deviceTime = track->getDeviceCurrentTime();
  NSTimeInterval trackTimeRemaining = track->getDuration() - track->getPosition();
  [_track->track playAtTime:deviceTime + trackTimeRemaining];
}

string Track::getTrackName() {
  return string(_fileName);
}