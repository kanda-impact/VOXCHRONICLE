//
//  MapSelector.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/10/7.
//
//

#include "SimpleAudioEngine.h"
#include "MapSelector.h"

bool MapSelector::init() {
  if (!CCLayer::init()) {
    return false;
  }
  
  CCMenuItemImage* leftArrow = CCMenuItemImage::create("left_arrow.png",
                                                       "left_arrow_selected.png",
                                                       this,
                                                       menu_selector(MapSelector::leftButtonPressed));
  CCMenuItemImage* rightArrow = CCMenuItemImage::create("right_arrow.png",
                                                        "right_arrow_selected.png",
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
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("decide.caf");
  _selectedMap = (Map*)_nextMaps->objectAtIndex(0);
}

void MapSelector::rightButtonPressed(cocos2d::CCObject *sender) {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("decide.caf");
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