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
#include <deque>
#include <string>
#include <boost/shared_ptr.hpp>
#include "macros.h"

#include "cocos2d.h"
#include "Track.h"

namespace VISS {
  class Music : public cocos2d::CCObject {
   private:
    int _trackCount;
    std::vector< std::deque<boost::shared_ptr<Track> > > _tracks;
   private:
    void update(float dt);
   public:
    Music();
    Music(int trackCount);
    ~Music();
    boost::shared_ptr<Track> getTrack(int trackNumber);
    boost::shared_ptr<Track> getNextTrack(int trackNumber);
    bool pushTrack(const std::string* fileName, int trackNumber);
    bool pushTrack(Track* track, int trackNumber);
    bool setTrack(const std::string* fileName, int trackNumber, int index);
    bool setTrack(Track* track, int trackNumber, int index);
    bool play();
    void stop();
    void pause();
  };
}

#endif /* defined(__VOXCHRONICLE__Music__) */
