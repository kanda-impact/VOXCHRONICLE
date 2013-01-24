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
  ALBuffer* buffer;
  ALSource* source;
  ALDevice* device;
  ALContext* context;
};

Track::Track(const char* fileName) : _track(new VISS::Track::AudioTrack) {
  NSString* file = [NSString stringWithUTF8String:fileName];
  _fileName = string(fileName);
  
  _track->device = [[ALDevice deviceWithDeviceSpecifier:nil] retain];
  _track->context = [[ALContext contextOnDevice:_track->device attributes:nil] retain];
  [OpenALManager sharedInstance].currentContext = _track->context;
  [OALAudioSession sharedInstance].handleInterruptions = YES;
  [OALAudioSession sharedInstance].allowIpod = NO;
  [OALAudioSession sharedInstance].honorSilentSwitch = YES;
  
  // Take all 32 sources for this channel.
  // (we probably won't use that many but what the heck!)
  _track->source = [[ALChannelSource channelWithSources:32] retain];
  
  // Preload the buffers so we don't have to load and play them later.
  _track->buffer = [[[OpenALManager sharedInstance]
                  bufferFromFile:file] retain];
}

Track::~Track() {
  [_track->buffer release];
  [_track->source release];
  [_track->device release];
  [_track->context release];
}

bool Track::play() {
  [_track->source play:_track->buffer];
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