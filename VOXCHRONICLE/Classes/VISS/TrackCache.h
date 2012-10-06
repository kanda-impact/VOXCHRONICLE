//
//  TrackCache.h
//  VOXCHRONICLE
//
//  Created by giginet on 2012/10/6.
//
//

#ifndef __VOXCHRONICLE__TrackCache__
#define __VOXCHRONICLE__TrackCache__

#include <iostream>
#include <map>
#include "Track.h"

using namespace VISS;
using namespace std;

namespace VISS {
  class TrackCache {
   private:
    CCDictionary* _cache;
    static TrackCache* _instance;
   public:
    static TrackCache* sharedCache();
    static void deleteCache();
    TrackCache();
    ~TrackCache();
    Track* addTrack(string trackName);
    void purgeAllTracks();
    
    //TrackCache(const TrackCache& r);
    //TrackCache& operator=(const TrackCache& r);
  };
}
#endif /* defined(__VOXCHRONICLE__TrackCache__) */
