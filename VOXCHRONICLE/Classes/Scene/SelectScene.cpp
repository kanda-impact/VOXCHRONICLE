//
//  SelectScene.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/2/26.
//
//

#include "SelectScene.h"
#include "TitleScene.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "FileUtils.h"

bool SelectScene::init() {
  if ( !CCLayer::init() ) {
    return false;
  }
  CCDirector* director = CCDirector::sharedDirector();
  
  CCSprite* background = CCSprite::create("select_background.png");
  background->setPosition(ccp(director->getWinSize().width / 2.0f, director->getWinSize().height / 2.0f));
  this->addChild(background);
  
  CCMenuItemImage* easyButton = CCMenuItemImage::create("easy_button.png",
                                                        "easy_button_pressed.png",
                                                        this,
                                                        menu_selector(SelectScene::onEasyButtonPressed));
  CCMenuItemImage* hardButton = CCMenuItemImage::create("hard_button.png",
                                                        "hard_button_pressed.png",
                                                        this,
                                                        menu_selector(SelectScene::onHardButtonPressed));
  CCMenu* mainMenu = CCMenu::create(easyButton, hardButton, NULL);
  mainMenu->alignItemsHorizontallyWithPadding(135);
  
  mainMenu->setPosition(ccp(director->getWinSize().width / 2.0f, 100));
  this->addChild(mainMenu);
  
  CCMenuItemImage* backButton = CCMenuItemImage::create("back_down.png", "back_down_pressed.png", this, menu_selector(SelectScene::onBackButtonPressed));
  CCMenu* backMenu = CCMenu::create(backButton, NULL);
  backMenu->setPosition(ccp(director->getWinSize().width / 2.0f, 17.5));
  this->addChild(backMenu);
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(FileUtils::getFilePath("Music/general/menu.mp3").c_str(), true);
  return true;
}

SelectScene::SelectScene() {
}

SelectScene::~SelectScene() {
}

void SelectScene::onEasyButtonPressed(cocos2d::CCObject *sender) {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/start.mp3").c_str());
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
  CCScene* scene = CCScene::create();
  TitleScene* layer = TitleScene::create();
  scene->addChild(layer);
  CCTransitionSlideInB* transition = CCTransitionSlideInB::create(0.25f, scene);
  CCDirector::sharedDirector()->replaceScene(transition);
}