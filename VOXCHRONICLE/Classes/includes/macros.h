//
//  macros.h
//  VOXCHRONICLE
//
//  Created by giginet on 2012/8/31.
//
//

#ifndef VOXCHRONICLE_macros_h
#define VOXCHRONICLE_macros_h

#define IS_IOS (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#define IS_WIN32 (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#if IS_IOS
#define FONT_NAME "Arial-BoldMT"
#else
#define FONT_NAME "Arial-BoldMT"
#endif

#endif
