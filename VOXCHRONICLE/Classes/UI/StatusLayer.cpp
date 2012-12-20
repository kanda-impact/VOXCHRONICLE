//
//  StatusLayer.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/12/16.
//
//

#include "StatusLayer.h"
#include "FileUtils.h"
#include <boost/lexical_cast.hpp>
#include <sstream>

StatusLayer::StatusLayer() {
  CCSprite* hpLabel = CCSprite::create(FileUtils::getFilePath("Image/Main/UI/proto/hp.png").c_str());
  hpLabel->setPosition(ccp(88, 300));
  this->addChild(hpLabel);
  CCSprite* mpLabel = CCSprite::create(FileUtils::getFilePath("Image/Main/UI/proto/mp.png").c_str());
  mpLabel->setPosition(ccp(88, 270));
  this->addChild(mpLabel);
  
  _currentHPLabel = CCLabelAtlas::create("0", FileUtils::getFilePath("Image/Main/UI/proto/hp_numbers.png").c_str(), 17, 18, '0');
  _currentHPLabel->retain();
  _currentHPLabel->setPosition(ccp(134, 300));
  _currentHPLabel->setAnchorPoint(ccp(0.5f, 0.5f));
  _maxHPLabel = CCLabelAtlas::create("0", FileUtils::getFilePath("Image/Main/UI/proto/hp_numbers.png").c_str(), 17, 18, '0');
  _maxHPLabel->retain();
  _maxHPLabel->setPosition(ccp(198, 300));
  _maxHPLabel->setAnchorPoint(ccp(0.5f, 0.5f));
  this->addChild(_currentHPLabel);
  this->addChild(_maxHPLabel);
  CCSprite* slash = CCSprite::create(FileUtils::getFilePath("Image/Main/UI/proto/slash.png").c_str());
  slash->setPosition(ccp(168, 300));
  this->addChild(slash);
  _mpChips = CCArray::create();
  _mpChips->retain();
  
  CCSprite* stageLabel = CCSprite::create(FileUtils::getFilePath("Image/Main/UI/proto/stage.png").c_str());
  stageLabel->setPosition(ccp(42, 260));
  this->addChild(stageLabel);
  
  _levelLabel = CCLabelAtlas::create("10", FileUtils::getFilePath("Image/Main/UI/proto/stage_numbers.png").c_str(), 35, 45, '0');
  _levelLabel->setPosition(ccp(0, 270));
  this->addChild(_levelLabel);
  
  _lifeGaugeBackground = CCSprite::create(FileUtils::getFilePath("Image/Main/UI/proto/gauge_bg.png").c_str());
  _lifeGaugeBackground->setAnchorPoint(ccp(0.0f, 0.5f));
  _lifeGaugeBackground->setPosition(ccp(230, 301));
  this->addChild(_lifeGaugeBackground);
  
  _lifeGauge = CCSprite::create(FileUtils::getFilePath("Image/Main/UI/proto/gauge.png").c_str());
  _lifeGauge->setAnchorPoint(ccp(0.0f, 0.5f));
  _lifeGauge->setPosition(ccp(230, 301));
  this->addChild(_lifeGauge);
}

StatusLayer::~StatusLayer() {
  _maxHPLabel->release();
  _currentHPLabel->release();
  _mpChips->release();
  _timeMarker->release();
}

void StatusLayer::setMarkerDuration(float d) {
  if (_timeMarker != NULL) {
    this->removeChild(_timeMarker, true);
    _timeMarker = NULL;
  }
  _timeMarker = CCSprite::create(FileUtils::getFilePath("Image/Main/UI/proto/marker0.png").c_str());
  CCArray* frames = CCArray::create();
  for (int i = 0; i < 4; ++i) {
    stringstream ss;
    ss << "Image/Main/UI/proto/marker" << i << ".png";
    CCSpriteFrame* frame = CCSpriteFrame::create(FileUtils::getFilePath(ss.str().c_str()).c_str(), CCRectMake(0, 0, 24, 24));
    frames->addObject(frame);
  }
  CCAnimation* animation = CCAnimation::createWithSpriteFrames(frames);
  animation->setDelayPerUnit(d);
  animation->setRestoreOriginalFrame(true);
  _timeMarker->retain();
  _timeMarker->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
  int width = CCDirector::sharedDirector()->getWinSize().width;
  _timeMarker->setPosition(ccp(width / 2, 20));
  this->addChild(_timeMarker);
}

void StatusLayer::setCurrentHP(int hp) {
  char str[4];
  sprintf(str, "%03d", hp);
  _currentHPLabel->setString(str);
  _lifeGauge->setScaleX(1.0f * hp);
}

void StatusLayer::setMaxHP(int hp) {
  char str[4];
  sprintf(str, "%03d", hp);
  _maxHPLabel->setString(str);
  _lifeGaugeBackground->setScaleX(1.0f * hp);
}

void StatusLayer::setCurrentMP(int mp) {
  int count = _mpChips->count();
  string filepath;
  for (int i = 0; i < count; ++i) {
    CCSprite* chip = (CCSprite*)_mpChips->objectAtIndex(i);
    if (i < mp) {
      filepath = FileUtils::getFilePath("Image/Main/UI/proto/mp_on.png");
    } else {
      filepath = FileUtils::getFilePath("Image/Main/UI/proto/mp_off.png");
    }
    chip->setTexture(CCTextureCache::sharedTextureCache()->addImage(filepath.c_str()));
    
  }
}


void StatusLayer::setMaxMP(int mp) {
  int count = _mpChips->count();
  if (count > mp) {
    for (int i = mp; i < count; ++i) {
      CCSprite* chip = (CCSprite*)_mpChips->objectAtIndex(i);
      this->removeChild(chip, true);
      _mpChips->removeObjectAtIndex(i);
      
    }
  } else if (count < mp) {
    for (int i = count; i < mp; ++i) {
      CCSprite* chip = CCSprite::create(FileUtils::getFilePath("Image/Main/UI/proto/mp_on.png").c_str());
      chip->setPosition(ccp(110 + 20 * i, 270));
      _mpChips->addObject(chip);
      this->addChild(chip);
    }
  }
}

void StatusLayer::setLevel(int level) {
  char str[2];
  sprintf(str, "%02d", level);
  _levelLabel->setString(str);
}