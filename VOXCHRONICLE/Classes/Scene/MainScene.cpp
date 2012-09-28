//
//  MainScene.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/8/28.
//
//

#include <sstream>
#include <cstdlib>
#include <boost/random.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>

#include "MainScene.h"

using namespace cocos2d;
using namespace VISS;

bool MainScene::init() {
  if ( !CCLayer::init() ) {
    return false;
  }
  _music = new Music(3);
  _music->setTrackDidBackFunction(boost::bind(&MainScene::trackDidBack, this, _1, _2, _3));
  _music->setTrackDidFinishFunction(boost::bind(&MainScene::trackDidFinishPlaying, this, _1, _2, _3, _4));
  _music->setTrackWillFinishFunction(boost::bind(&MainScene::trackWillFinishPlaying, this, _1, _2, _3, _4));
  
  _music->pushTrack("dub_voxnormal00.wav", 0);
  _music->pushTrack("dub_basschord00.wav", 1);
  _music->pushTrack("dub_drum00.wav", 2);
  
  CCDirector* director = CCDirector::sharedDirector();
  _controller = Controller::create();
  CCSize size = director->getWinSize();
  this->addChild(_controller);
  
  return true;
}

void MainScene::onEnterTransitionDidFinish() {
  _music->play();
}

void MainScene::trackDidBack(Music *music, Track *currentTrack, int trackNumber) {
  if (trackNumber == 0) {
    std::cout << "back" << std::endl;
  }
}

void MainScene::trackWillFinishPlaying(Music *music, Track *currentTrack, Track *nextTrack, int trackNumber) {
  if (trackNumber == 0) {
    int index = _controller->currentTriggerIndex();
    std::ostringstream os;
    if (index == -1) {
      os << "dub_silent.wav";
    } else {
      os << "dub_voxnormal0" << index << ".wav";
    }
    _music->pushTrack(os.str().c_str(), 0);
  } else if (trackNumber == 1) {
    _music->pushTrack("dub_basschord00.wav", 1);
  } else if (trackNumber == 2) {
    _music->pushTrack("dub_drum00.wav", 2);
  }
}

void MainScene::trackDidFinishPlaying(Music *music, Track *finishedTrack, Track *nextTrack, int trackNumber) {
  if (trackNumber == 0) {
    _controller->resetAllTriggers();
    std::cout << "next Track" << std::endl;
  }
}
