//
//  Ground.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/2/1.
//
//

#include "Ground.h"
#include "FileUtils.h"
#include <boost/lexical_cast.hpp>

using namespace boost;

const int GROUND_HEIGHT = 123;

Ground::Ground(const char* prefix, int frameCount) {
  CCDirector* director = CCDirector::sharedDirector();
  _prefix = prefix;
  _frameCount = frameCount;
  this->initWithFile(FileUtils::getFilePath((_prefix + string("_ground0.png")).c_str()).c_str());
  CCPoint center = ccp(director->getWinSize().width / 2.0f, GROUND_HEIGHT / 2.0f);
  this->setPosition(center);
  _currentFrame = 0;
}

void Ground::nextFrame() {
  _currentFrame = (_currentFrame + 1) % _frameCount;
  string filename = (_prefix + string("_ground") + lexical_cast<string>(_currentFrame) + string(".png"));
  this->setTexture(CCTextureCache::sharedTextureCache()->addImage(FileUtils::getFilePath(filename.c_str()).c_str()));
}