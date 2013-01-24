//
//  BufferCache.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/10/6.
//
//

#include "BufferCache.h"
#include "OpenALManager.h"
#include <boost/lexical_cast.hpp>

using namespace VISS;

struct VISS::BufferCache::Dictionary {
  NSMutableDictionary* dictionary;
};

BufferCache* BufferCache::_instance;

BufferCache* BufferCache::sharedCache() {
  if(!_instance) _instance = new BufferCache();
  return _instance;
}

void BufferCache::deleteCache() {
  if(_instance){ delete _instance; _instance = 0; }
}

BufferCache::BufferCache(): _cache(new VISS::BufferCache::Dictionary){
  _cache->dictionary = [[NSMutableDictionary dictionary] retain];
}

BufferCache::~BufferCache() {
  [_cache->dictionary release];
}

ALBuffer* BufferCache::addBuffer(string trackName) {
  NSString* key = [NSString stringWithCString:trackName.c_str() encoding:NSASCIIStringEncoding];
  if ( [_cache->dictionary objectForKey:key] ) {
    ALBuffer* buffer = (ALBuffer*)[_cache->dictionary objectForKey:key];
    return buffer;
  }
  ALBuffer* buffer = [[[OpenALManager sharedInstance]
                       bufferFromFile:[NSString stringWithCString:trackName.c_str() encoding:NSASCIIStringEncoding]] retain];
  [_cache->dictionary setObject:buffer forKey:key];
  return buffer;
}

void BufferCache::purgeAllBuffers() {
  [_cache->dictionary removeAllObjects];
}