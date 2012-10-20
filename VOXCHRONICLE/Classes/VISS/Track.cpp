//
//  Track.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/8/31.
//
//

#include "Track.h"

// It is wrapper class for ObjectAL::OALAudioTrack.

using namespace std;
using namespace VISS;

Track::Track(const char* fileName) {

}

Track::~Track() {

}

bool Track::play() {
  return false;
}

void Track::playAfterTime(float time) {
}
  
void Track::stop() {
}
  
void Track::pause() {
}

bool Track::isPlaying() {
  return false;
}

float Track::getDuration() {
  return 0.0f;
}

float Track::getPosition() {
  return 0.0f;
}

float Track::getDeviceCurrentTime() {
  return 0.0f;
}

void Track::setVolume(float v) {
}

void Track::playAfterTrack(VISS::Track *track) {
}