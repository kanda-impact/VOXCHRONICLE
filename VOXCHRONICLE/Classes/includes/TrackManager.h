//
//  TrackManager.h
//  VOXCHRONICLE
//
//  Created by giginet on 2012/12/30.
//
//

#ifndef __VOXCHRONICLE__TrackManager__
#define __VOXCHRONICLE__TrackManager__

#include <iostream>

class TrackManager {
 public:
  static void preloadMusics(const char* prefix, const char* list);
  static void preloadSE(const char* list);
  static void purgeMusics();
  static void purgeSE();

};

#endif /* defined(__VOXCHRONICLE__TrackManager__) */
