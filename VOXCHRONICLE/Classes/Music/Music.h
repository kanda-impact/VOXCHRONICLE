//
//  Music.h
//  VOXCHRONICLE
//
//  Created by giginet on 2012/8/31.
//
//

#ifndef __VOXCHRONICLE__Music__
#define __VOXCHRONICLE__Music__

#include <iostream>
#include <vector>
#include <string>
#include "cocos2d.h"
#include "Track.h"

namespace VISS {
  class Music {
  private:
    int _trackCount;
    std::vector<Track*> _tracks;
    std::vector<Track*> _nextTracks;
  public:
    Music();
    Music(int trackCount);
    ~Music();
    Track* getTrack(int trackNumber);
    bool setNextTrack(std::string* fileName, int trackNumber);
    bool setNextTrack(Track* track, int trackNumber);
    bool play();
    bool stop();
    bool pause();
  };
}

#endif /* defined(__VOXCHRONICLE__Music__) */
