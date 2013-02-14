//
//  Buffer.h
//  VOXCHRONICLE
//
//  Created by giginet on 2013/2/14.
//
//

#ifndef __VOXCHRONICLE__Buffer__
#define __VOXCHRONICLE__Buffer__

#include <iostream>
#include "cocos2d.h"
#include "macros.h"
#include <boost/shared_ptr.hpp>

using namespace cocos2d;

namespace VISS {
  class Buffer :public CCObject {
   public:
#if IS_IOS
    struct BufferWrapper;
#endif
   private:
    std::string _trackName;
#if IS_IOS
    boost::shared_ptr<BufferWrapper> _wrapper;
#endif
   public:
    Buffer(const char* trackName);
    ~Buffer();
#if IS_IOS
    BufferWrapper* getBuffer();
#endif
  };
}

#endif /* defined(__VOXCHRONICLE__Buffer__) */
