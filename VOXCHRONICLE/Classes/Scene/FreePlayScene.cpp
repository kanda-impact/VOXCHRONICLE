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
  CCArray* items2 = CCArray::create();
  CCLuaValueArray* array = lua->getArray("stages");
  int i = 0;
  for (CCLuaValueArrayIterator it = array->begin(); it != array->end(); ++it, ++i) {
    string name = it->stringValue();
    Map* map = new Map(name.c_str());
    map->autorelease();
    CCLabelTTF* label = CCLabelTTF::create(map->getName().c_str(), FONT_NAME, 24);
    CCMenuItemLabel* item = CCMenuItemLabel::create(label, this, menu_selector(FreePlayScene::onMenuItemPressed));
    item->setUserObject(map);
    if (i < 7) {
      items->addObject(item);
    } else {
      items2->addObject(item);
    }
  }
  
  CCMenu* menu = CCMenu::createWithArray(items);
  menu->setPosition(ccp(140, 160));
  menu->alignItemsVerticallyWithPadding(20);
  this->addChild(menu);
  if (items2->count() > 0) {
    CCMenu* menu2 = CCMenu::createWithArray(items2);
    menu2->setPosition(ccp(340, 160));
    menu2->alignItemsVerticallyWithPadding(20);
    this->addChild(menu2);
  }
  
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
