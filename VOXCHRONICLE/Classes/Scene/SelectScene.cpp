//
//  SelectScene.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/2/26.
//
//

#include "SelectScene.h"
#include "MainScene.h"
#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
#include "FileUtils.h"

bool SelectScene::init() {
  if ( !CCLayer::init() ) {
    return false;
  }
  
  _thumbnails = CCArray::create();
  _thumbnails->retain();
  
  CCDirector* director = CCDirector::sharedDirector();
  
  CCSprite* background = CCSprite::create("select_background.png");
  background->setPosition(ccp(director->getWinSize().width / 2.0f, director->getWinSize().height / 2.0f));
  this->addChild(background);
  
  CCMenuItemImage* easyButton = CCMenuItemImage::create("select_easy.png",
                                                        "select_easy.png",
                                                        this,
                                                        menu_selector(SelectScene::onEasyButtonPressed));
  CCMenuItemImage* hardButton = CCMenuItemImage::create("select_hard.png",
                                                        "select_hard.png",
                                                        this,
                                                        menu_selector(SelectScene::onHardButtonPressed));
  CCMenu* mainMenu = CCMenu::create(easyButton, hardButton, NULL);
  mainMenu->alignItemsHorizontallyWithPadding(-5);
  
  mainMenu->setPosition(ccp(director->getWinSize().width / 2.0f, 140));
  this->addChild(mainMenu);
  
  CCMenuItemImage* backButton = CCMenuItemImage::create("back_down.png",
                                                        "back_down_pressed.png",
                                                        this,
                                                        menu_selector(SelectScene::onBackButtonPressed));
  CCMenu* backMenu = CCMenu::create(backButton, NULL);
  backMenu->setPosition(ccp(director->getWinSize().width / 2.0f, 30));
  this->addChild(backMenu);
  
  CCSprite* map = CCSprite::create("select_map.png");
  map->setPosition(ccp(director->getWinSize().width / 2.0f, 255));
  this->addChild(map);
  
  this->createThumbnails();
  
  return true;
}

SelectScene::SelectScene() {
}

SelectScene::~SelectScene() {
  _thumbnails->release();
}

void SelectScene::createThumbnails() {
  const int x[] = {190, 240, 290, 165, 215, 265, 315};
  const int y[] = {262, 262, 262, 303, 303, 303, 303};
  // マップによって切り替えたり、セーブデータによって切り替えたりはあとで実装する
  for (int i = 0; i < 7; ++i) {
    CCSprite* sprite = CCSprite::create("select_thumbnail_disable.png");
    sprite->setPosition(ccp(x[i], y[i]));
    this->addChild(sprite);
    _thumbnails->addObject(sprite);
  }
}

void SelectScene::onEasyButtonPressed(cocos2d::CCObject *sender) {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/decide.mp3").c_str());
  MainScene* layer = MainScene::create();
  CCScene* scene = CCScene::create();
  scene->addChild(layer);
  CCTransitionFade* transition = CCTransitionFade::create(0.5, scene);
  CCDirector::sharedDirector()->replaceScene(transition);
  CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
}

void SelectScene::onHardButtonPressed(cocos2d::CCObject *sender) {
}

void SelectScene::onBackButtonPressed(cocos2d::CCObject *sender) {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/decide.mp3").c_str());
  CCScene* scene = CCScene::create();
  MainMenuScene* layer = new MainMenuScene(false);
  layer->autorelease();
  scene->addChild(layer);
  CCTransitionSlideInB* transition = CCTransitionSlideInB::create(0.25f, scene);
  CCDirector::sharedDirector()->replaceScene(transition);
}