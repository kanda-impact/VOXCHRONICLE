//
//  MapSelector.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/10/7.
//
//

#include "SimpleAudioEngine.h"
#include "MapSelector.h"
#include "FileUtils.h"

bool MapSelector::init() {
  if (!CCLayer::init()) {
    return false;
  }
  
  CCMenuItemImage* leftArrow = CCMenuItemImage::create(FileUtils::getFilePath("selector_easy.png").c_str(),
                                                       FileUtils::getFilePath("selector_easy_selected.png").c_str(),
                                                       this,
                                                       menu_selector(MapSelector::leftButtonPressed));
  CCMenuItemImage* rightArrow = CCMenuItemImage::create(FileUtils::getFilePath("selector_hard.png").c_str(),
                                                        FileUtils::getFilePath("selector_hard_selected.png").c_str(),
                                                        this,
                                                        menu_selector(MapSelector::rightButtonPressed));
  CCMenu* menu = CCMenu::create(leftArrow, rightArrow, NULL);
  menu->alignItemsHorizontallyWithPadding(135);
  this->addChild(menu);
  _nextMaps = NULL;
  _selectedMap = NULL;
  _effectID = 0;
  return true;
}

void MapSelector::onEnter() {
  CCLayer::onEnter();
  //_effectID = SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/selector.mp3").c_str(), true);
}

MapSelector::MapSelector() {
}

MapSelector::~MapSelector() {
  if (_effectID != 0) {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopEffect(_effectID);
  }
  _nextMaps->release();
}

void MapSelector::leftButtonPressed(cocos2d::CCObject *sender) {
  if (_effectID != 0) {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopEffect(_effectID);
  }
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/selector_decide.mp3").c_str());
  _selectedMap = (Map*)_nextMaps->objectAtIndex(0);
}

void MapSelector::rightButtonPressed(cocos2d::CCObject *sender) {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/selector_decide.mp3").c_str());
  _selectedMap = (Map*)_nextMaps->objectAtIndex(1);
}

void MapSelector::setNextMaps(cocos2d::CCArray *maps) {
  if (_nextMaps) {
    _nextMaps->release();
  }
  if (maps) {
    maps->retain();
  }
  _nextMaps = maps;
}

Map* MapSelector::getSelectedMap() {
  return _selectedMap;
}