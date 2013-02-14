//
//  Buffer.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/2/14.
//
//

#include "Buffer.h"
#include "ObjectAL.h"

using namespace VISS;

struct Buffer::BufferWrapper {
  ALBuffer* buffer;
};

Buffer::Buffer(const char* trackName): _wrapper(new Buffer::BufferWrapper) {
  ALBuffer* buffer = [[[OpenALManager sharedInstance]
                       bufferFromFile:[NSString stringWithCString:trackName encoding:NSASCIIStringEncoding]] retain];
  _wrapper->buffer = buffer;
  _trackName = trackName;
}

Buffer::~Buffer() {
  [_wrapper->buffer release];
  NSLog(@"release %s", _trackName.c_str());
}

Buffer::BufferWrapper* Buffer::getBuffer() {
  return _wrapper.get();
}