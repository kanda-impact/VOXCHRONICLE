//
//  BufferCache.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/10/6.
//
//

#include "BufferCache.h"
#include <boost/lexical_cast.hpp>

using namespace VISS;

BufferCache* BufferCache::_instance;

BufferCache* BufferCache::sharedCache() {
  if(!_instance) _instance = new BufferCache();
  return _instance;
}

void BufferCache::deleteCache() {
  if(_instance){ delete _instance; _instance = 0; }
}

BufferCache::BufferCache() {
  _cache = CCDictionary::create();
  _cache->retain();
}

BufferCache::~BufferCache() {
  _cache->release();
}

Buffer* BufferCache::addBuffer(const char* trackName) {
  if (_cache->objectForKey(trackName)) {
    return (Buffer*)_cache->objectForKey(trackName);
  }
  Buffer* buffer = new Buffer(trackName);
  buffer->autorelease();
  _cache->setObject(buffer, trackName);
  return buffer;
}

void BufferCache::purgeAllBuffers() {
  _cache->removeAllObjects();
}