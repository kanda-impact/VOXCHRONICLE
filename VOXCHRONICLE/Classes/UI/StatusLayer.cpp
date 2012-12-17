//
//  StatusLayer.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/12/16.
//
//

#include "StatusLayer.h"
#include "FileUtils.h"

StatusLayer::StatusLayer() {
  CCSprite* hpLabel = CCSprite::create(FileUtils::getFilePath("Image/Main/UI/proto/hp.png").c_str());
  hpLabel->setPosition(ccp(80, 300));
  this->addChild(hpLabel);
  CCSprite* mpLabel = CCSprite::create(FileUtils::getFilePath("Image/Main/UI/proto/mp.png").c_str());
  mpLabel->setPosition(ccp(80, 270));
  this->addChild(mpLabel);
}