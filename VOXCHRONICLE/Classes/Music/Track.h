//
//  Track.h
//  VOXCHRONICLE
//
//  Created by giginet on 2012/8/31.
//
//

#ifndef __VOXCHRONICLE__Track__
#define __VOXCHRONICLE__Track__

#include <iostream>
#include <string>

class Track {
 private:
  std::string* _fileName;
 public:
  Track(std::string* fileName);
  ~Track();
  bool play();
  bool stop();
  bool pause();
  bool isPlaying();
  float getDuration();
  float getPosition();
};

#endif /* defined(__VOXCHRONICLE__Track__) */
