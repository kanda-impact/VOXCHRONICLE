//
//  BufferCache.h
//  VOXCHRONICLE
//
//  Created by giginet on 2012/10/6.
//
//

#ifndef __VOXCHRONICLE__TrackCache__
#define __VOXCHRONICLE__TrackCache__

#include <iostream>
#include <map>
#include <boost/shared_ptr.hpp>
#include "Track.h"
#include "Buffer.h"

using namespace VISS;
using namespace std;

namespace VISS {
  class BufferCache {
   private:
    CCDictionary* _cache;
    static BufferCache* _instance;
   public:
    static BufferCache* sharedCache();
    static void deleteCache();
    BufferCache();
    ~BufferCache();
    Buffer* addBuffer(const char* trackName);
    void purgeAllBuffers();
  };
}
#endif /* defined(__VOXCHRONICLE__TrackCache__) */
