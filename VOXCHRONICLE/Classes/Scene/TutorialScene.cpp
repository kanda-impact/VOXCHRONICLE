//
//  TutorialScene.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/3/3.
//
//

#include "TutorialScene.h"
#include "FileUtils.h"
#include "SimpleAudioEngine.h"
#include "MainMenuScene.h"
#include "LuaObject.h"
#include "Map.h"
#include "MainScene.h"

typedef enum {
  TutorialLayerTagMenu,
  TutorialLayerTagBack
} TutorialLayerTag;

bool TutorialLayer::init() {
  if (!CCLayer::init()) {
    return false;
  }
  
  CCDirector* director = CCDirector::sharedDirector();
  CCPoint center = ccp(director->getWinSize().width / 2.0f, director->getWinSize().height / 2.0f);
  
  CCSprite* background = CCSprite::create("select_background.png");
  background->setPosition(center);
  this->addChild(background);
  
  CCMenuItemImage* tutorial0 = CCMenuItemImage::create("tutorial_button0.png",
                                                       "tutorial_button0_pressed.png",
                                                       this,
                                                       menu_selector(TutorialLayer::onTutorialButtonPressed));
  tutorial0->setTag(0);
  CCMenuItemImage* tutorial1 = CCMenuItemImage::create("tutorial_button1.png",
                                                       "tutorial_button1_pressed.png",
                                                       this,
                                                       menu_selector(TutorialLayer::onTutorialButtonPressed));
  tutorial1->setTag(1);
  CCMenuItemImage* tutorial2 = CCMenuItemImage::create("tutorial_button2.png",
                                                       "tutorial_button2_pressed.png",
                                                       this,
                                                       menu_selector(TutorialLayer::onTutorialButtonPressed));
  tutorial2->setTag(2);
  CCMenuItemImage* back = CCMenuItemImage::create("tutorial_back.png",
                                                  "tutorial_back_pressed.png",
                                                  this,
                                                  menu_selector(TutorialLayer::onBackButtonPressed));
  CCMenu* tutorialMenu = CCMenu::create(tutorial0, tutorial1, tutorial2, NULL);
  CCMenu* backMenu = CCMenu::createWithItem(back);
  
  tutorialMenu->alignItemsVerticallyWithPadding(40);
  
  tutorialMenu->setPosition(ccp(225, center.y));
  backMenu->setPosition(ccp(480 - 40, center.y));
  
  this->addChild(tutorialMenu, 0, TutorialLayerTagMenu);
  this->addChild(backMenu, 0, TutorialLayerTagBack);
  
  _selectNumber = -1;
  
  return true;
}

void TutorialLayer::onEnterTransitionDidFinish() {
  CCLayer::onEnterTransitionDidFinish();
  if (!SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()) {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(FileUtils::getFilePath("Music/general/menu.mp3").c_str(), true);
  }
}

void TutorialLayer::onTutorialButtonPressed(cocos2d::CCObject *sender) {
  SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/tutorial_decide.mp3").c_str());
  _selectNumber = ((CCNode*)sender)->getTag();
  CCMenu* main = (CCMenu*)this->getChildByTag(TutorialLayerTagMenu);
  CCMenu* back = (CCMenu*)this->getChildByTag(TutorialLayerTagBack);
  main->setEnabled(false);
  back->setEnabled(false);
  CCMenuItemImage* item = (CCMenuItemImage*)sender;
  item->runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(CCFadeTo::create(0.05f, 128),
                                                                           CCFadeTo::create(0.05f, 255))));
  
  this->scheduleOnce(schedule_selector(TutorialLayer::onGameStart), 3.0f); // 遅延してゲーム開始
}

void TutorialLayer::onBackButtonPressed(cocos2d::CCObject *sender) {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/menu_cancel.mp3").c_str());
  CCScene* scene = CCScene::create();
  MainMenuScene* layer = new MainMenuScene(false);
  layer->autorelease();
  scene->addChild(layer);
  CCTransitionSlideInR* transition = CCTransitionSlideInR::create(0.25f, scene);
  CCDirector::sharedDirector()->replaceScene(transition);
}

void TutorialLayer::onGameStart(cocos2d::CCObject *sender) {
  LuaObject* lua = LuaObject::create("setting");
  shared_ptr<CCLuaValueArray> array = lua->getArray("tutorials");
  int i = 0;
  for (CCLuaValueArrayIterator it = array->begin(); it != array->end(); ++it) {
    if (i == _selectNumber) {
      string mapName = it->stringValue();
      Map* map = new Map(mapName.c_str());
      map->autorelease();
      MainScene* layer = new MainScene();
      layer->autorelease();
      layer->init(map);
      layer->setBackScene(MainBackSceneTutorial);
      CCScene* scene = CCScene::create();
      scene->addChild(layer);
      CCTransitionFade* fade = CCTransitionFade::create(0.5f, scene);
      CCDirector::sharedDirector()->replaceScene(fade);
      return;
    }
    ++i;
  }
}