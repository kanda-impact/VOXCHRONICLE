//
//  MainScene.h
//  VOXCHRONICLE
//
//  Created by giginet on 2012/8/28.
//
//

#ifndef __VOXCHRONICLE__MainScene__
#define __VOXCHRONICLE__MainScene__

#include <iostream>
#include "cocos2d.h"
#include "Track.h"
#include "Music.h"

using namespace VISS;

class MainScene : public cocos2d::CCLayer {
 private:
  VISS::Music* _music;
  void onEnterTransitionDidFinish();
  
  void trackDidBack(Music* music, Track* currentTrack, int trackNumber);
  void trackWillFinishPlaying(Music* music, Track* currentTrack, Track* nextTrack, int trackNumber);
  void trackDidFinishPlaying(Music* music, Track* finishedTrack, Track* nextTrack, int trackNumber);
  
 public:
  virtual bool init();
  
  LAYER_CREATE_FUNC(MainScene);
};

#endif /* defined(__VOXCHRONICLE__MainScene__) */
