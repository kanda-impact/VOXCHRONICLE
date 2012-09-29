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
#include <boost/function.hpp>
#include "macros.h"

#include "cocos2d.h"
#include "Track.h"

namespace VISS {
  class Music : public cocos2d::CCObject {
   private:
    int _trackCount;
    std::vector< std::deque<boost::shared_ptr<Track> > > _tracks;
    std::vector<bool> _backed;
    std::vector<bool> _willFinish;
    void update(float dt);
    boost::function<void (Music*, Track*, Track*, int)> _trackWillFinishFunction;
    boost::function<void (Music*, Track*, Track*, int)> _trackDidFinishFunction;
    boost::function<void (Music*, Track*, int)> _trackDidBackFunction;
    void willFinishPlaying(Track* track, int trackCount);
    void didFinishPlaying(Track* track, int trackCount);
    void didBacking(Track* track, int trackCount);
   public:
    Music();
    Music(int trackCount);
    ~Music();
    boost::shared_ptr<Track> getTrack(int trackNumber);
    boost::shared_ptr<Track> getNextTrack(int trackNumber);
    bool pushTrack(const char* fileName, int trackNumber);
    bool pushTrack(const char* fileName, int trackNumber, int repeat);
    bool pushTrack(Track* track, int trackNumber);
    bool setTrack(const char* fileName, int trackNumber, int index);
    bool setTrack(Track* track, int trackNumber, int index);
    bool play();
    void stop();
    void pause();
    void setTrackWillFinishFunction(boost::function<void (Music*, Track*, Track*, int)>);
    void setTrackDidFinishFunction(boost::function<void (Music*, Track*, Track*, int)>);
    void setTrackDidBackFunction(boost::function<void (Music*, Track*, int)>);
  };
}

#endif /* defined(__VOXCHRONICLE__Music__) */
