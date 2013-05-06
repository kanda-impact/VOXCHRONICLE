//
//  FreePlayScene.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 1/9/13.
//
//

#include "FreePlayScene.h"
#include "LuaObject.h"
#include "macros.h"
#include "Map.h"
#include "FileUtils.h"
#include "ExtraScene.h"
#include "SaveData.h"
#include <boost/algorithm/string/predicate.hpp>

FreePlayScene* FreePlayScene::create(const char *script, bool unlock) {
  FreePlayScene* scene = new FreePlayScene();
  scene->autorelease();
  if (!scene->init(script, unlock)) {
    return NULL;
  }
  return scene;
}

CCScene* FreePlayScene::scene(const char* script, bool unlock) {
  CCScene* scene = CCScene::create();
  
  FreePlayScene* layer = FreePlayScene::create(script, unlock);
  scene->addChild(layer);
  
  return scene;
}

bool FreePlayScene::init(const char* script, bool unlock) {
  if ( !CCLayer::init() ) {
    return false;
  }
  this->setTouchEnabled(true);
  
  LuaObject* lua = LuaObject::create(script);
  CCArray* items = CCArray::create();
  for (int i = 0; i < 3; ++i) {
    items->addObject(CCArray::create());
  }
  
  // ハードコード安定
  _backScene = MainBackSceneFreePlay;
  if (boost::algorithm::istarts_with(script, "debug")) {
    _backScene = MainBackSceneDebug;
  } else if (boost::algorithm::istarts_with(script, "freeplay")) {
    _backScene = MainBackSceneFreePlay;
  } else if (boost::algorithm::istarts_with(script, "soundtest")) {
    _backScene = MainBackSceneSoundTest;
  }
  
  CCDirector* director = CCDirector::sharedDirector();
  CCSprite* bg = CCSprite::create("select_background.png");
  bg->setPosition(ccp(director->getWinSize().width / 2.0, director->getWinSize().height / 2.0));
  this->addChild(bg);
  
  shared_ptr<CCLuaValueArray> array = lua->getArray("stages");
  int i = 0;
  for (CCLuaValueArrayIterator it = array->begin(); it != array->end(); ++it, ++i) {
    int col = floor(i / 5);
    string name = it->stringValue();
    Map* map = new Map(name.c_str());
    map->autorelease();
    CCSprite* buttonSprite = CCSprite::create("free.png");
    CCLabelTTF* fontLabel = CCLabelTTF::create(map->getName().c_str(), "Helvetica", 24);
    fontLabel->setAnchorPoint(ccp(0.5, 0.5));
    fontLabel->setPosition(ccp(125 / 2.0, 40 / 2.0));
    fontLabel->setColor(ccc3(240, 240, 240));
    buttonSprite->addChild(fontLabel);
    CCSprite* buttonPressedSprite = CCSprite::create("free_pressed.png");
    CCSprite* buttonDisableSprite = CCSprite::create("free_disable.png");
    CCMenuItemSprite* item = CCMenuItemSprite::create(buttonSprite,
                                                      buttonPressedSprite,
                                                      buttonDisableSprite,
                                                      this,
                                                      menu_selector(FreePlayScene::onMenuItemPressed));
    item->setUserObject(map);
    item->setEnabled(SaveData::sharedData()->isClearedMap(map->getIdentifier().c_str()) || unlock);
    CCArray* array = (CCArray*)items->objectAtIndex(col);
    if (col >= 3) break;
    array->addObject(item);
  }
  
  for (int j = i + 1; j < 15; ++j) { // 透明ボタンの追加 足りない分を透明ボタンでpad
    CCSprite* buttonSprite = CCSprite::create("free.png");
    CCMenuItemSprite* item = CCMenuItemSprite::create(buttonSprite, buttonSprite);
    item->setVisible(false);
    int col = floor(j / 5);
    CCArray* array = (CCArray*)items->objectAtIndex(col);
    array->addObject(item);
  }
  
  CCMenuItemImage* back = CCMenuItemImage::create("dictionary_back.png",
                                                  "dictionary_back_pressed.png",
                                                  this,
                                                  menu_selector(FreePlayScene::onBackButtonPressed));
  CCArray* last = (CCArray*)items->objectAtIndex(2);
  last->addObject(back);
  
  for (int i = 0; i < 3; ++i) {
    CCArray* array = (CCArray*)items->objectAtIndex(i);
    if (array->count() > 0) {
      CCMenu* menu = CCMenu::createWithArray(array);
      menu->setPosition(ccp(88 + 150 * i, 150));
      menu->alignItemsVerticallyWithPadding(15);
      this->addChild(menu);
    }
    
  }
  
  string description = lua->getString("description");
  CCLabelTTF* descriptionLabel = CCLabelTTF::create(description.c_str(), "Helvetica", 16);
  descriptionLabel->setPosition(ccp(240, 300));
  this->addChild(descriptionLabel);
  
  return true;
}

void FreePlayScene::onEnterTransitionDidFinish() {
  CCLayer::onEnterTransitionDidFinish();
  if (!SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()) {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(FileUtils::getFilePath("Music/general/menu.mp3").c_str(), true);
  }
}

void FreePlayScene::onMenuItemPressed(cocos2d::CCObject *sender) {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/start.mp3").c_str());
  Map* map = (Map*)((CCNode*)sender)->getUserObject();
  MainScene* layer = new MainScene();
  layer->autorelease();
  layer->init(map);
  layer->setBackScene(_backScene);
  CCScene* scene = CCScene::create();
  scene->addChild(layer);
  CCTransitionFade* transition = CCTransitionFade::create(0.5, scene);
  CCDirector::sharedDirector()->replaceScene(transition);
}

void FreePlayScene::onBackButtonPressed() {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/menu_cancel.mp3").c_str());  
  ExtraScene* layer = ExtraScene::create();
  CCScene* scene = CCScene::create();
  scene->addChild(layer);
  CCTransitionSlideInB* transition = CCTransitionSlideInB::create(0.25f, scene);
  CCDirector::sharedDirector()->replaceScene(transition);
}
