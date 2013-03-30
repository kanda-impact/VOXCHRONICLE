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
  
  CCDirector* director = CCDirector::sharedDirector();
  
  CCNode* leftSprite = CCNode::create();
  //Map* leftMap = (Map*)_nextMaps->objectAtIndex(0);
  CCSprite* leftThumbnail = CCSprite::create("cyber_hexagon.png");
  if (leftThumbnail != NULL) {
    leftThumbnail->setPosition(ccp(0, -22.5));
    leftSprite->addChild(leftThumbnail);
  }
  CCSprite* leftFrame = CCSprite::create("selector_easy.png");
  leftSprite->addChild(leftFrame);
  leftSprite->setContentSize(leftFrame->getTextureRect().size);
  leftSprite->setPosition(ccp(62.5, 100));
  
  CCMenuItemSprite* leftArrow = CCMenuItemSprite::create(leftSprite,
                                                         leftSprite,
                                                         this, menu_selector(MapSelector::leftButtonPressed));
  
  CCNode* rightSprite = CCNode::create();
  //Map* rightMap = (Map*)_nextMaps->objectAtIndex(1);
  CCSprite* rightThumbnail = CCSprite::create("cyber_hexagon.png");
  if (rightThumbnail != NULL) {
    rightThumbnail->setPosition(ccp(0, -22.5));
    rightSprite->addChild(rightThumbnail);
  }
  CCSprite* rightFrame = CCSprite::create("selector_hard.png");
  rightSprite->addChild(rightFrame);
  rightSprite->setContentSize(rightFrame->getTextureRect().size);
  rightSprite->setPosition(ccp(62.5, 100));
  
  CCMenuItemSprite* rightArrow = CCMenuItemSprite::create(rightSprite,
                                                          rightSprite,
                                                          this, menu_selector(MapSelector::rightButtonPressed));
  
  CCMenu* menu = CCMenu::create(leftArrow, rightArrow, NULL);
  CCSize offset = rightFrame->getTextureRect().size;
  menu->setAnchorPoint(ccp(0.5, 0.5));
  menu->setPosition(ccp(director->getWinSize().width / 2.0, director->getWinSize().height / 2.0));
  menu->alignItemsHorizontallyWithPadding(135);
  this->addChild(menu);
  _nextMaps = NULL;
  _selectedMap = NULL;
  _effectID = 0;
  return true;
}

void MapSelector::onEnter() {
  CCLayer::onEnter();
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