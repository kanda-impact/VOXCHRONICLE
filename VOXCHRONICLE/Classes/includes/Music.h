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
#include <boost/function.hpp>
#include "macros.h"

#include "cocos2d.h"
#include "Track.h"

namespace VISS {
  class Music : public cocos2d::CCObject {
   private:
    int _trackCount;
    int _measureCount;
    CCArray* _tracks;
    void update(float dt);
    boost::function<void (Music*, Track*, Track*, int)> _trackWillFinishFunction;
    boost::function<void (Music*, Track*, Track*, int)> _trackDidFinishFunction;
    boost::function<void (Music*, Track*, int)> _trackDidBackFunction;
    void onTrackWillFinish();
    void onTrackDidFinish();
    void onTrackDidBack();
    void setScheduleForMain();
    void setSchedule(Track* track);
    void setScheduleDelay(float delay);
   public:
    Music();
    Music(int trackCount);
    virtual ~Music();
    Track* getTrack(int trackNumber);
    Track* getNextTrack(int trackNumber);
    Track* pushTrack(const char* fileName, int trackNumber);
    Track* pushTrack(const char* fileName, int trackNumber, int repeat);
    Track* pushTrack(Track* track, int trackNumber);
    Track* setTrack(const char* fileName, int trackNumber, int index);
    Track* setTrack(Track* track, int trackNumber, int index);
    bool play();
    void stop();
    void pause();
    void setTrackWillFinishFunction(boost::function<void (Music*, Track*, Track*, int)>);
    void setTrackDidFinishFunction(boost::function<void (Music*, Track*, Track*, int)>);
    void setTrackDidBackFunction(boost::function<void (Music*, Track*, int)>);
    void removeAllNextTracks();
    Track* getCurrentMainTrack();
  };
}

#endif /* defined(__VOXCHRONICLE__Music__) */
