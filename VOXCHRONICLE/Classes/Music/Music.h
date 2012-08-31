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
#include <boost/shared_ptr.hpp>
#include "macros.h"

#include "cocos2d.h"
#include "Track.h"

namespace VISS {
  class Music : public cocos2d::CCObject {
   private:
    int _trackCount;
    std::vector< boost::shared_ptr<Track> > _tracks;
    std::vector< boost::shared_ptr<Track> > _nextTracks;
   private:
    void update(float dt);
   public:
    Music();
    Music(int trackCount);
    ~Music();
    boost::shared_ptr<Track> getTrack(int trackNumber);
    bool setTrack(const std::string* fileName, int trackNumber);
    bool setTrack(Track* track, int trackNumber);
    bool setNextTrack(const std::string* fileName, int trackNumber);
    bool setNextTrack(Track* track, int trackNumber);
    bool play();
    void stop();
    void pause();
  };
}

#endif /* defined(__VOXCHRONICLE__Music__) */
