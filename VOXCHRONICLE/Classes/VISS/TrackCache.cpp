//
//  TrackCache.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/10/6.
//
//

#include "TrackCache.h"

using namespace VISS;

TrackCache* TrackCache::_instance;

TrackCache* TrackCache::sharedCache() {
  if(!_instance) _instance = new TrackCache;
  return _instance;
}

void TrackCache::deleteCache() {
  if(_instance){ delete _instance; _instance = 0; }
}

TrackCache::TrackCache() {
  _cache = CCDictionary::create();
  _cache->retain();
}

TrackCache::~TrackCache() {
  _cache->release();
}

Track* TrackCache::addTrack(string trackName) {
  if (_cache->objectForKey(trackName) ) {
    Track* track = (Track*)_cache->objectForKey(trackName);
    Track* newTrack = new Track(trackName.c_str());
    _cache->removeObjectForKey(trackName);
    _cache->setObject(newTrack, trackName);
    return track;
  } else {
    Track* track = new Track(trackName.c_str());
    Track* newTrack = new Track(trackName.c_str());
    _cache->setObject(newTrack, trackName);
    return track;
  }
}

void TrackCache::purgeAllTracks() {
  _cache->removeAllObjects();
}