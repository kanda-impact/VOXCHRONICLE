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
#include "MainScene.h"
#include "LuaObject.h"

StatusLayer::StatusLayer(const char* scriptName) {
  LuaObject* obj = LuaObject::create(scriptName);
  CCLuaEngine* engine = obj->getLuaEngineWithLoad();
  lua_State* L = engine->getLuaState();
  _prefix = obj->getString("prefix");
  lua_getfield(L, lua_gettop(L), "buildSkin");
  if (lua_isfunction(L, lua_gettop(L))) {
    engine->pushCCObject(this, "CCLayer");
    if (lua_pcall(L, 1, 0, 0)) {
      cout << lua_tostring(L, lua_gettop(L)) << endl;
    }
  }
  _mpChips = CCArray::create();
  _mpChips->retain();
  
  CCMenu* pause = CCMenu::create(CCMenuItemImage::create(FileUtils::getFilePath("Image/pause_button.png").c_str(),
                                                         FileUtils::getFilePath("Image/pause_button_disable.png").c_str(),
                                                         this,
                                                         menu_selector(StatusLayer::onPauseButtonPressed)), NULL);
  pause->setPosition(ccp(440, 300));
  this->addChild(pause);
  _timeMarker = NULL;
}

StatusLayer::~StatusLayer() {
  _mpChips->release();
  if (_timeMarker) {
    _timeMarker->release();
  }
}

void StatusLayer::setMarkerDuration(float d) {
  if (_timeMarker != NULL) {
    _timeMarker->release();
    this->removeChild(_timeMarker, true);
    _timeMarker = NULL;
  }
  _timeMarker = CCSprite::create(FileUtils::getFilePath("Image/marker0.png").c_str());
  _timeMarker->retain();
  CCArray* frames = CCArray::create();
  for (int i = 0; i < 4; ++i) {
    stringstream ss;
    ss << "Image/" << "marker" << i << ".png";
    CCSpriteFrame* frame = CCSpriteFrame::create(FileUtils::getFilePath(ss.str().c_str()).c_str(), CCRectMake(0, 0, 24, 24));
    frames->addObject(frame);
  }
  CCAnimation* animation = CCAnimation::createWithSpriteFrames(frames);
  animation->setDelayPerUnit(d);
  animation->setRestoreOriginalFrame(true);
  _timeMarker->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
  int width = CCDirector::sharedDirector()->getWinSize().width;
  _timeMarker->setPosition(ccp(width / 2, 20));
  this->addChild(_timeMarker);
}

void StatusLayer::setCurrentHP(int hp) {
  char str[4];
  sprintf(str, "%03d", hp);
  CCLabelAtlas* currentHPLabel = (CCLabelAtlas*)this->getChildByTag(CurrentHPLabelTag);
  currentHPLabel->setString(str);
  CCSprite* lifeGauge = (CCSprite*)this->getChildByTag(LifeGaugeTag);
  lifeGauge->setScaleX(1.0f * hp * 0.5);
}

void StatusLayer::setMaxHP(int hp) {
  char str[4];
  sprintf(str, "%03d", hp);
  CCLabelAtlas* maxHPLabel = (CCLabelAtlas*)this->getChildByTag(MaxHPLabelTag);
  maxHPLabel->setString(str);
  CCSprite* lifeGaugeBackground = (CCSprite*)this->getChildByTag(LifeGaugeBackgroundTag);
  lifeGaugeBackground->setScaleX(1.0f * hp * 0.5);
}

void StatusLayer::setCurrentMP(int mp) {
  int count = _mpChips->count();
  string filepath;
  for (int i = 0; i < count; ++i) {
    CCSprite* chip = (CCSprite*)_mpChips->objectAtIndex(i);
    if (i < mp) {
      filepath = _prefix + "_mp_on.png";
    } else {
      filepath = _prefix + "_mp_off.png";
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
  } else {
    const int colLength = 8;
    for (int i = count; i < mp; ++i) {
      int col = i % colLength;
      int row = floor(i / colLength);
      CCSprite* chip = CCSprite::create((_prefix + "_mp_on.png").c_str());
      chip->setPosition(ccp(300 + 15 * col, 308 - 15 * row));
      _mpChips->addObject(chip);
      this->addChild(chip);
    }
  }
}

void StatusLayer::setLevel(int level) {
  char str[2];
  sprintf(str, "%02d", level);
  CCLabelAtlas* levelLabel = (CCLabelAtlas*)this->getChildByTag(LevelLabelTag);
  levelLabel->setString(str);
}

void StatusLayer::onPauseButtonPressed(CCObject* sender) {
  MainScene* scene = (MainScene*)this->getParent();
  if (scene->getState() != VCStateGameOver) {
    scene->setPause(true);
  }
}