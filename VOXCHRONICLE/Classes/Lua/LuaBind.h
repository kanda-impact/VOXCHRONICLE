//
//  LuaBind.h
//  VOXCHRONICLE
//
//  Created by giginet on 2012/10/6.
//
//

#ifndef __VOXCHRONICLE__LuaBind__
#define __VOXCHRONICLE__LuaBind__

#include <iostream>

extern "C" {
#include "tolua++.h"
#include "tolua_fix.h"
}

#include <map>
#include <string>
#include "tolua_fix.h"
#include "cocos2d.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

TOLUA_API int tolua_voxchronicle_open(lua_State* tolua_S);

#endif /* defined(__VOXCHRONICLE__LuaBind__) */
