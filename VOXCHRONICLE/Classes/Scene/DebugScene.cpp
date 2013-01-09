//
//  DebugScene.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 1/9/13.
//
//

#include "DebugScene.h"
#include "LuaObject.h"
#include "macros.h"

static const char* DEBUG_SCRIPT = "Script/debug.lua";

CCScene* DebugScene::scene() {
  CCScene* scene = CCScene::create();
  
  DebugScene* layer = DebugScene::create();
  
  scene->addChild(layer);
  
  return scene;
}

bool DebugScene::init() {
  if ( !CCLayer::init() ) {
    return false;
  }
  this->setTouchEnabled(true);
  
  LuaObject* lua = new LuaObject(DEBUG_SCRIPT);
  CCArray* items = CCArray::create();
  CCLuaValueArray* array = lua->getArray("stages");
  for (CCLuaValueArrayIterator it = array->begin(); it != array->end(); ++it) {
    string name = it->stringValue();
    CCLabelTTF* label = CCLabelTTF::create(name.c_str(), FONT_NAME, 16);
    CCMenuItemLabel* item = CCMenuItemLabel::create(label, this, menu_selector(DebugScene::onMenuItemPressed));
    items->addObject(item);
  }
  CCMenu* menu = CCMenu::createWithArray(items);
  menu->setPosition(ccp(240, 160));
  menu->alignItemsVertically();
  this->addChild(menu);
  
  return true;
}

void DebugScene::onMenuItemPressed(cocos2d::CCObject *sender) {
}
