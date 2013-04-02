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

static const char* DEBUG_SCRIPT = "Script/debug.lua";

FreePlayScene* FreePlayScene::create(const char *script) {
  FreePlayScene* scene = new FreePlayScene();
  scene->autorelease();
  if (!scene->init(script)) {
    return NULL;
  }
  return scene;
}

CCScene* FreePlayScene::scene(const char* script) {
  CCScene* scene = CCScene::create();
  
  FreePlayScene* layer = FreePlayScene::create(script);
  scene->addChild(layer);
  
  return scene;
}

bool FreePlayScene::init(const char* script) {
  if ( !CCLayer::init() ) {
    return false;
  }
  this->setTouchEnabled(true);
  
  LuaObject* lua = new LuaObject(DEBUG_SCRIPT);
  CCArray* items = CCArray::create();
  CCLuaValueArray* array = lua->getArray("stages");
  for (CCLuaValueArrayIterator it = array->begin(); it != array->end(); ++it) {
    string name = it->stringValue();
    Map* map = new Map(name.c_str());
    map->autorelease();
    CCLabelTTF* label = CCLabelTTF::create(map->getName().c_str(), FONT_NAME, 16);
    CCMenuItemLabel* item = CCMenuItemLabel::create(label, this, menu_selector(FreePlayScene::onMenuItemPressed));
    items->addObject(item);
    item->setUserObject(map);
  }
  CCMenu* menu = CCMenu::createWithArray(items);
  menu->setPosition(ccp(240, 160));
  menu->alignItemsVerticallyWithPadding(15);
  this->addChild(menu);
  
  return true;
}

void FreePlayScene::onEnterTransitionDidFinish() {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(FileUtils::getFilePath("Music/general/menu.mp3").c_str(), true);
}

void FreePlayScene::onMenuItemPressed(cocos2d::CCObject *sender) {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/start.mp3").c_str());
  Map* map = (Map*)((CCNode*)sender)->getUserObject();
  MainScene* layer = new MainScene();
  layer->autorelease();
  layer->init(map);
  CCScene* scene = CCScene::create();
  scene->addChild(layer);
  CCTransitionFade* transition = CCTransitionFade::create(0.5, scene);
  CCDirector::sharedDirector()->replaceScene(transition);
  CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
}
