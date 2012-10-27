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
  
  CCMenuItemImage* leftArrow = CCMenuItemImage::create(FileUtils::getFilePath("Image/Main/UI/left_arrow.png").c_str(),
                                                       FileUtils::getFilePath("Image/Main/UI/left_arrow_selected.png").c_str(),
                                                       this,
                                                       menu_selector(MapSelector::leftButtonPressed));
  CCMenuItemImage* rightArrow = CCMenuItemImage::create(FileUtils::getFilePath("Image/Main/UI/right_arrow.png").c_str(),
                                                        FileUtils::getFilePath("Image/Main/UI/right_arrow_selected.png").c_str(),
                                                        this,
                                                        menu_selector(MapSelector::rightButtonPressed));
  CCMenu* menu = CCMenu::create(leftArrow, rightArrow, NULL);
  menu->alignItemsHorizontallyWithPadding(180);
  this->addChild(menu);
  _nextMaps = NULL;
  return true;
}

MapSelector::MapSelector() {
}

void MapSelector::leftButtonPressed(cocos2d::CCObject *sender) {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/decide.mp3").c_str());
  _selectedMap = (Map*)_nextMaps->objectAtIndex(0);
}

void MapSelector::rightButtonPressed(cocos2d::CCObject *sender) {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/decide.mp3").c_str());
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
  if (maps && maps->count() > 0) {
    _selectedMap = (Map*)maps->objectAtIndex(0);
  }
}

Map* MapSelector::getSelectedMap() {
  return _selectedMap;
}