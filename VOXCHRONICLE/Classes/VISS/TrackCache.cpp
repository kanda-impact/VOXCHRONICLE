//
//  TrackCache.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/10/6.
//
//

#include "TrackCache.h"
#include <boost/lexical_cast.hpp>

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

Track* TrackCache::addTrack(string trackName, int mod) {
  string key = trackName + boost::lexical_cast<string>(mod);
  if (_cache->objectForKey(key) ) {
    Track* track = (Track*)_cache->objectForKey(key);
    return track;
  }
  Track* track = new Track(trackName.c_str());
  _cache->setObject(track, key);
  return track;
}

void TrackCache::purgeAllTracks() {
  _cache->removeAllObjects();
}