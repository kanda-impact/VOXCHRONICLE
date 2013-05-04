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

void MapSelector::onEnter() {
  CCLayer::onEnter();
}

MapSelector::MapSelector(CCArray* nextMaps) {
  CCDirector* director = CCDirector::sharedDirector();
  
  _nextMaps = nextMaps;
  _nextMaps->retain();
  CCNode* leftSprite = CCNode::create();
  Map* leftMap = (Map*)_nextMaps->objectAtIndex(0);
  CCSprite* leftThumbnail = CCSprite::create(leftMap->getThumbnailImageName().c_str());
  if (leftThumbnail != NULL) {
    leftThumbnail->setPosition(ccp(0, -22.5));
    leftSprite->addChild(leftThumbnail);
  }
  CCSprite* leftFrame = CCSprite::create("selector_easy.png");
  leftSprite->addChild(leftFrame, 0, 1);
  leftSprite->setContentSize(leftFrame->getTextureRect().size);
  leftSprite->setPosition(ccp(62.5, 100));
  leftFrame->runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(CCFadeTo::create(1.5, 128),
                                                                                CCFadeTo::create(1.5, 255))));
  
  
  CCMenuItemSprite* leftArrow = CCMenuItemSprite::create(leftSprite,
                                                         leftSprite,
                                                         this, menu_selector(MapSelector::buttonPressed));
  leftArrow->setUserObject(leftMap);
  
  CCNode* rightSprite = CCNode::create();
  Map* rightMap = (Map*)_nextMaps->objectAtIndex(1);
  CCSprite* rightThumbnail = CCSprite::create(rightMap->getThumbnailImageName().c_str());
  if (rightThumbnail != NULL) {
    rightThumbnail->setPosition(ccp(0, -22.5));
    rightSprite->addChild(rightThumbnail);
  }
  CCSprite* rightFrame = CCSprite::create("selector_hard.png");
  rightSprite->addChild(rightFrame, 0, 1);
  rightSprite->setContentSize(rightFrame->getTextureRect().size);
  rightSprite->setPosition(ccp(62.5, 100));
  rightFrame->runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(CCFadeTo::create(1.5, 128),
                                                                                 CCFadeTo::create(1.5, 255))));
  
  CCMenuItemSprite* rightArrow = CCMenuItemSprite::create(rightSprite,
                                                          rightSprite,
                                                          this, menu_selector(MapSelector::buttonPressed));
  rightArrow->setUserObject(rightMap);
  
  CCMenu* menu = CCMenu::create(leftArrow, rightArrow, NULL);
  CCSize offset = rightFrame->getTextureRect().size;
  menu->setAnchorPoint(ccp(0.5, 0.5));
  menu->setPosition(ccp(director->getWinSize().width / 2.0, director->getWinSize().height / 2.0));
  menu->alignItemsHorizontallyWithPadding(135);
  this->addChild(menu);
  _selectedMap = NULL;
  _effectID = 0;
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("selector.mp3", true);
}

MapSelector::~MapSelector() {
  if (_effectID != 0) {
    //CocosDenshion::SimpleAudioEngine::sharedEngine()->stopEffect(_effectID);
  }
  _nextMaps->release();
  if (_selectedMap) {
    _selectedMap->release();
  }
}

void MapSelector::buttonPressed(cocos2d::CCObject *sender) {
  CCMenuItemSprite* item = (CCMenuItemSprite*)sender;
  CCSprite* sprite = (CCSprite*)item->getNormalImage();
  CCSprite* frame = (CCSprite*)sprite->getChildByTag(1);
  frame->runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(CCFadeTo::create(0.01, 128),
                                                                            CCFadeTo::create(0.01, 255))));
  
  CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/selector_decide.mp3").c_str());
  if (_selectedMap) {
    _selectedMap->release();
    _selectedMap = NULL;
  }
  _selectedMap = (Map*)item->getUserObject();
  if (_selectedMap) {
    _selectedMap->retain();
  }
}

Map* MapSelector::getSelectedMap() {
  return _selectedMap;
}