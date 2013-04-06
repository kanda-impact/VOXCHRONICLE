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
#include "MainScene.h"
#include "FileUtils.h"
#include "ExtraScene.h"
#include "SaveData.h"

static const char* DEBUG_SCRIPT = "Script/debug.lua";

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
  
  LuaObject* lua = new LuaObject(DEBUG_SCRIPT);
  CCArray* items = CCArray::create();
  for (int i = 0; i < 3; ++i) {
    items->addObject(CCArray::create());
  }
  
  CCDirector* director = CCDirector::sharedDirector();
  CCSprite* bg = CCSprite::create("select_background.png");
  bg->setPosition(ccp(director->getWinSize().width / 2.0, director->getWinSize().height / 2.0));
  this->addChild(bg);
  
  CCLuaValueArray* array = lua->getArray("stages");
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
  
  CCMenuItemImage* back = CCMenuItemImage::create("select_back.png",
                                                  "select_back_pressed.png",
                                                  this,
                                                  menu_selector(FreePlayScene::onBackButtonPressed));
  CCArray* last = (CCArray*)items->objectAtIndex(2);
  last->addObject(back);
  
  for (int i = 0; i < 3; ++i) {
    CCArray* array = (CCArray*)items->objectAtIndex(i);
    if (array->count() > 0) {
      CCMenu* menu = CCMenu::createWithArray(array);
      menu->setPosition(ccp(88 + 150 * i, 160));
      menu->alignItemsVerticallyWithPadding(15);
      this->addChild(menu);
    }
    
  }
  
  return true;
}

void FreePlayScene::onEnterTransitionDidFinish() {

}

void FreePlayScene::onMenuItemPressed(cocos2d::CCObject *sender) {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/start.mp3").c_str());
  Map* map = (Map*)((CCNode*)sender)->getUserObject();
  MainScene* layer = new MainScene();
  layer->autorelease();
  layer->init(map);
  CCScene* scene = CCScene::create();
  scene->addChild(layer);
  CCTransitionFade* transition = CCTransitionFade::create(0.5, scene);
  CCDirector::sharedDirector()->replaceScene(transition);
}

void FreePlayScene::onBackButtonPressed() {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/cancel.mp3").c_str());  
  ExtraScene* layer = ExtraScene::create();
  CCScene* scene = CCScene::create();
  scene->addChild(layer);
  CCTransitionFade* transition = CCTransitionFade::create(0.5, scene);
  CCDirector::sharedDirector()->replaceScene(transition);
}
