//
//  Ground.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/2/1.
//
//

#include "Ground.h"
#include "FileUtils.h"

Ground::Ground(const char* prefix) {
  CCDirector* director = CCDirector::sharedDirector();
  _prefix = prefix;
  string p(prefix);
  
  _background = CCSprite::create(FileUtils::getFilePath((p + string("_floor0.png")).c_str()).c_str());
  _background->retain();
  this->setAnimaton();
  CCPoint center = ccp(director->getWinSize().width / 2.0f, director->getWinSize().height / 2.0f);
  _background->setPosition(center);
  this->addChild(_background);
  this->stop();
}

void Ground::play() {
  _background->stopAllActions();
  this->setAnimaton();
}

void Ground::stop() {
  _background->stopAllActions();
}

void Ground::setAnimaton() {
  string p(_prefix);
  CCAnimation* animation = CCAnimation::create();
  animation->addSpriteFrame(CCSpriteFrame::create(FileUtils::getFilePath((p + string("_floor0.png")).c_str()).c_str(), CCRectMake(0, 0, 480, 320)));
  animation->addSpriteFrame(CCSpriteFrame::create(FileUtils::getFilePath((p + string("_floor1.png")).c_str()).c_str(), CCRectMake(0, 0, 480, 320)));
  animation->addSpriteFrame(CCSpriteFrame::create(FileUtils::getFilePath((p + string("_floor2.png")).c_str()).c_str(), CCRectMake(0, 0, 480, 320)));
  animation->setLoops(-1);
  animation->setDelayPerUnit(10.0 / 60.0);
  _background->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
}