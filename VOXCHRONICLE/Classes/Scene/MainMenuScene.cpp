//
//  MainMenuScene.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/3/3.
//
//

#include "MainMenuScene.h"
#include "SelectScene.h"
#include "FileUtils.h"
#include "SimpleAudioEngine.h"
#include "TutorialScene.h"
#include "ExtraScene.h"

MainMenuScene::MainMenuScene(bool fromTitle) {
  CCDirector* director = CCDirector::sharedDirector();
  CCPoint center = ccp(director->getWinSize().width / 2.0f, director->getWinSize().height / 2.0f);
  CCSprite* background = CCSprite::create("mainmenu_background.png");
  background->setPosition(center);
  CCMenuItemImage* start = CCMenuItemImage::create("mainmenu_start.png",
                                                   "mainmenu_start_pressed.png",
                                                   this,
                                                   menu_selector(MainMenuScene::onStartPressed));
  CCMenuItemImage* tutorial = CCMenuItemImage::create("mainmenu_tutorial.png",
                                                      "mainmenu_tutorial_pressed.png",
                                                      this,
                                                      menu_selector(MainMenuScene::onTutorialPressed));
  CCMenuItemImage* extra = CCMenuItemImage::create("mainmenu_extra.png",
                                                   "mainmenu_extra_pressed.png",
                                                   this,
                                                   menu_selector(MainMenuScene::onExtraPressed));
  CCMenu* menu = CCMenu::create(tutorial, start, extra, NULL);
  menu->setPosition(center);
  menu->alignItemsHorizontallyWithPadding(0);
  this->addChild(menu);
  _fromTitle = fromTitle;
}

void MainMenuScene::onEnterTransitionDidFinish() {
  if (_fromTitle) {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(FileUtils::getFilePath("Music/general/menu.mp3").c_str(), true);
  }
}

void MainMenuScene::onStartPressed(cocos2d::CCObject *sender) {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/decide.mp3").c_str());
  CCScene* scene = CCScene::create();
  SelectScene* layer = SelectScene::create();
  scene->addChild(layer);
  CCTransitionSlideInT* transition = CCTransitionSlideInT::create(0.25f, scene);
  CCDirector::sharedDirector()->pushScene(transition);
}

void MainMenuScene::onTutorialPressed(cocos2d::CCObject *sender) {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/decide.mp3").c_str());
  CCScene* scene = CCScene::create();
  TutorialLayer* layer = TutorialLayer::create();
  scene->addChild(layer);
  CCTransitionSlideInL* transition = CCTransitionSlideInL::create(0.25f, scene);
  CCDirector::sharedDirector()->pushScene(transition);
}

void MainMenuScene::onExtraPressed(cocos2d::CCObject *sender) {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/decide.mp3").c_str());
  CCScene* scene = CCScene::create();
  ExtraScene* layer = ExtraScene::create();
  scene->addChild(layer);
  CCTransitionSlideInR* transition = CCTransitionSlideInR::create(0.25f, scene);
  CCDirector::sharedDirector()->pushScene(transition);
}