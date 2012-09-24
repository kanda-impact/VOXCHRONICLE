//
//  MainScene.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/8/28.
//
//

#include "MainScene.h"
#include "Controller.h"

using namespace cocos2d;
using namespace VISS;

bool MainScene::init() {
  if ( !CCLayer::init() ) {
    return false;
  }
  _music = new Music(3);
  _music->pushTrack("dub_voxnormal00.wav", 0);
  _music->pushTrack("dub_voxnormal01.wav", 0);
  _music->pushTrack("dub_voxnormal02.wav", 0);
  _music->pushTrack("dub_voxnormal03.wav", 0);
  _music->pushTrack("dub_voxnormal04.wav", 0);
  _music->pushTrack("dub_voxnormal05.wav", 0);
  _music->pushTrack("dub_voxnormal06.wav", 0);
  _music->pushTrack("dub_voxnormal07.wav", 0);
  _music->pushTrack("dub_voxnormal04.wav", 0);
  _music->pushTrack("dub_voxnormal05.wav", 0);
  _music->pushTrack("dub_voxnormal06.wav", 0);
  _music->pushTrack("dub_voxnormal07.wav", 0);
  _music->pushTrack("dub_end.wav", 0);
  _music->pushTrack("dub_basschord00.wav", 1);
  _music->pushTrack("dub_basschord01.wav", 1);
  _music->pushTrack("dub_basschord02.wav", 1);
  _music->pushTrack("dub_basschord03.wav", 1);
  _music->pushTrack("dub_basschord04.wav", 1);
  _music->pushTrack("dub_basschord05.wav", 1);
  _music->pushTrack("dub_basschord06.wav", 1);
  _music->pushTrack("dub_basschord07.wav", 1);
  _music->pushTrack("dub_basschord04.wav", 1);
  _music->pushTrack("dub_basschord05.wav", 1);
  _music->pushTrack("dub_basschord06.wav", 1);
  _music->pushTrack("dub_basschord07.wav", 1);
  _music->pushTrack("dub_drum00.wav", 2);
  _music->pushTrack("dub_drum01.wav", 2);
  _music->pushTrack("dub_drum02.wav", 2);
  _music->pushTrack("dub_drum03.wav", 2);
  _music->pushTrack("dub_drum04.wav", 2);
  _music->pushTrack("dub_drum04.wav", 2);
  _music->pushTrack("dub_drum04.wav", 2);
  _music->pushTrack("dub_drum04.wav", 2);
  _music->pushTrack("dub_drum04.wav", 2);
  _music->pushTrack("dub_drum04.wav", 2);
  _music->pushTrack("dub_drum04.wav", 2);
  _music->pushTrack("dub_drum04.wav", 2);
  _music->pushTrack("dub_drum00.wav", 2, 3);
  _music->pushTrack("dub_drum04.wav", 2);

  CCDirector* director = CCDirector::sharedDirector();
  Controller* controller = Controller::create();
  CCSize size = director->getWinSize();
  this->addChild(controller);
  
  return true;
}

void MainScene::onEnterTransitionDidFinish() {
  _music->play();
}

