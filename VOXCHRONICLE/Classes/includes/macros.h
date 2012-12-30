//
//  macros.h
//  VOXCHRONICLE
//
//  Created by giginet on 2012/8/31.
//
//

#ifndef VOXCHRONICLE_macros_h
#define VOXCHRONICLE_macros_h
#include "cocos2d.h"

#define IS_IOS (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#define IS_WIN32 (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#define FONT_NAME "Arial-BoldMT"
#else
#define FONT_NAME "Arial-BoldMT"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <boost/lexical_cast.hpp>
#define LOG(__str) ( OutputDebugString(boost::lexical_cast<string>( __str ).c_str() ) )
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include <iostream>
#define LOG(__str) (cout << __str << endl)
#endif

#define VOX_COLOR ccc3(1, 255, 255)
#define LSK_COLOR ccc3(205, 43, 121)

#endif
