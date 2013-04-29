//
//  DictionaryScene.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/3/18.
//
//

#include "DictionaryScene.h"
#include "Enemy.h"
#include "LuaObject.h"
#include "FileUtils.h"
#include "ExtraScene.h"
#include "SaveData.h"

#include <boost/lexical_cast.hpp>

using namespace boost;

bool DictionaryScene::init() {
  if (!CCLayer::init()) {
    return false;
  }
  CCTextureCache::sharedTextureCache()->removeUnusedTextures();
  Enemy::loadLifeColors();
  LuaObject* lua = LuaObject::create("enemy.lua");
  lua_State* L = lua->getLuaEngineWithLoad()->getLuaState();
  lua_getglobal(L, "dictionary");
  shared_ptr<CCLuaValueArray> array = lua->getArray();
  _enemies = CCArray::create();
  _enemies->retain();
  _enemy = NULL;
  
  int defeatedCount = 0;
  for (CCLuaValueArrayIterator it = array->begin(); it != array->end();  ++it) {
    CCString* string = CCString::create(it->stringValue());
    _enemies->addObject(string);
    if ( 0 < SaveData::sharedData()->getDefeatedCount(it->stringValue().c_str()) ) {
      defeatedCount += 1;
    }
  }
  SaveData::sharedData()->setCountFor(SaveDataCountKeyDictionaryCount, defeatedCount);
  
  CCDirector* director = CCDirector::sharedDirector();
  
  CCSprite* background = CCSprite::create("select_background.png");
  background->setPosition(ccp(director->getWinSize().width / 2.0f, director->getWinSize().height / 2.0f));
  this->addChild(background);
  
  _nameLabel = CCLabelTTF::create("敵キャラ名", "Helvetica", 24, CCSizeMake(350, 30), kCCTextAlignmentLeft);
  _numberLabel = CCLabelTTF::create("生息地", "Helvetica", 16, CCSizeMake(50, 30), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
  _descriptionLabel = CCLabelTTF::create("ここに敵キャラの解説が入ります", "Helvetica", 16, CCSizeMake(440, 120), kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
  _nameLabel->setAnchorPoint(ccp(0.5f, 0.5f));
  _nameLabel->setPosition(ccp(200, 135));
  _numberLabel->setAnchorPoint(ccp(0.5f, 0.5f));
  _numberLabel->setPosition(ccp(450, 135));
  CCSprite* dictionaryWindow = CCSprite::create("dictionary_window.png");
  dictionaryWindow->setPosition(ccp(director->getWinSize().width / 2.0, 80));
  _descriptionLabel->setAnchorPoint(ccp(0.5f, 0.5f));
  _descriptionLabel->setPosition(ccp(director->getWinSize().width / 2.0f, 60));
  this->addChild(dictionaryWindow);
  this->addChild(_nameLabel);
  this->addChild(_numberLabel);
  this->addChild(_descriptionLabel);
  
  CCMenuItemImage* left = CCMenuItemImage::create("dictionary_cursor_left.png",
                                                  "dictionary_cursor_left_pressed.png",
                                                  this,
                                                  menu_selector(DictionaryScene::onCursorButtonPressed));
  CCMenuItemImage* right = CCMenuItemImage::create("dictionary_cursor_right.png",
                                                  "dictionary_cursor_right_pressed.png",
                                                  this,
                                                  menu_selector(DictionaryScene::onCursorButtonPressed));
  CCMenuItemImage* back = CCMenuItemImage::create("dictionary_back.png",
                                                  "dictionary_back_pressed.png",
                                                  this,
                                                  menu_selector(DictionaryScene::onBackButtonPressed));
  left->setTag(0);
  right->setTag(1);
  
  this->loadEnemyByIndex(0);
  
  CCMenu* menu = CCMenu::create(left, right, NULL);
  menu->setPosition(ccp(director->getWinSize().width / 2.0, 240));
  menu->alignItemsHorizontallyWithPadding(300);
  CCMenu* backMenu = CCMenu::create(back, NULL);
  this->addChild(backMenu);
  backMenu->setPosition(ccp(425, 32));
  this->addChild(menu);
  
  _cursor = 0;
  
  return true;
}

DictionaryScene::~DictionaryScene() {
  if (_enemy) {
    _enemy->release();
  }
  _enemies->release();
  CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}

void DictionaryScene::onEnterTransitionDidFinish() {
  CCLayer::onEnterTransitionDidFinish();
  SimpleAudioEngine::sharedEngine()->playBackgroundMusic("dictionary.mp3", true);
}

void DictionaryScene::loadEnemyByIndex(int idx) {
  CCString* script = (CCString*)_enemies->objectAtIndex(idx);
  if (_enemy) {
    this->removeChild(_enemy, true);
    _enemy->release();
  }
  _enemy = Enemy::createWithSpecies(script->getCString());
  _enemy->retain();
  _enemy->setRowAndCol(1, 0);
  
#if DEBUG
  bool isDefeated = true;
#else
  bool isDefeated = SaveData::sharedData()->getDefeatedCount(_enemy->getSpecies()->getIdentifier().c_str()) > 0; // 倒したかどうか
#endif
  
  CCDirector* director = CCDirector::sharedDirector();
  _enemy->setPosition(ccp(director->getWinSize().width / 2.0f, 160));
  this->addChild(_enemy);
  if (isDefeated) {
    _nameLabel->setString(_enemy->getName().c_str());
    _numberLabel->setString(lexical_cast<string>(idx + 1).c_str());
    _descriptionLabel->setString(_enemy->getSpecies()->getDescription().c_str());
    _enemy->setColor(ccc3(255, 255, 255));
  } else {
    _nameLabel->setString(this->repeatChar("?", _enemy->getName().size()).c_str());
    _numberLabel->setString(lexical_cast<string>(idx + 1).c_str());
    _descriptionLabel->setString(this->repeatChar("?", _enemy->getSpecies()->getDescription().size()).c_str());
    _enemy->setColor(ccc3(5, 5, 5));
    _enemy->setSilhouette();
  }
  CCTextureCache::sharedTextureCache()->removeAllTextures();
  Species::purgeSpeciesCache();
}

string DictionaryScene::repeatChar(const char *c, int times) {
  string str = string(c);
  for (int i = 0; i < times - 1; ++i) {
    str += string(c);
  }
  return str;
}

void DictionaryScene::onBackButtonPressed(cocos2d::CCObject *sender) {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/menu_cancel.mp3").c_str());
  ExtraScene* layer = ExtraScene::create();
  CCScene* scene = CCScene::create();
  scene->addChild(layer);
  CCTransitionSlideInB* transition = CCTransitionSlideInB::create(0.25f, scene);
  CCDirector::sharedDirector()->replaceScene(transition);
  SimpleAudioEngine::sharedEngine()->playBackgroundMusic("menu.mp3", true);
}

void DictionaryScene::onCursorButtonPressed(cocos2d::CCObject *sender) {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/paper.mp3").c_str());
  CCNode* node = (CCNode*)sender;
  int direction = -1 + node->getTag() * 2;
  int count = _enemies->count();
  _cursor = (count + _cursor + direction) % count;
  this->loadEnemyByIndex(_cursor);
}