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
#include "ALBuffer.h"
#include "Track.h"

using namespace VISS;
using namespace std;

namespace VISS {
  class BufferCache {
    struct Dictionary;
   private:
    boost::shared_ptr<Dictionary> _cache;
    static BufferCache* _instance;
   public:
    static BufferCache* sharedCache();
    static void deleteCache();
    BufferCache();
    ~BufferCache();
    ALBuffer* addBuffer(string trackName);
    void purgeAllBuffers();
  };
}
#endif /* defined(__VOXCHRONICLE__TrackCache__) */
