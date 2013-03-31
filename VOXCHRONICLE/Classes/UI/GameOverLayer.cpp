//
//  GameOverLayer.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/1/31.
//
//

#include "GameOverLayer.h"
#include "SimpleAudioEngine.h"
#include "FileUtils.h"
#include "TitleScene.h"
#include "macros.h"

GameOverLayer::GameOverLayer(MainScene* main) {
  _main = main;
  main->retain();
  this->buildUI();
}

GameOverLayer::~GameOverLayer() {
  if (_main) {
    _main->release();
  }
}

void GameOverLayer::buildUI() {
  CCSprite* gameover = CCSprite::create("gameover_label.png");
  CCDirector* director = CCDirector::sharedDirector();
  CCPoint center = CCPointMake(director->getWinSize().width / 2, director->getWinSize().height / 2);
  gameover->setPosition(center);
  gameover->runAction(CCSequence::create(CCDelayTime::create(3.0),
                                         CCMoveTo::create(0.1, ccp(director->getWinSize().width / 2, 200)),
                                         CCCallFunc::create(this, callfunc_selector(GameOverLayer::addGameOverButtons)),
                                         NULL));
  this->addChild(gameover);
}

void GameOverLayer::addGameOverButtons() {
  CCMenu* menu = CCMenu::create(CCMenuItemImage::create("replay.png", "replay_pressed.png", this, menu_selector(GameOverLayer::replayButtonPressed)),
                                CCMenuItemImage::create("title.png", "title_pressed.png", this, menu_selector(GameOverLayer::titleButtonPressed)),
                                NULL);
  CCDirector* director = CCDirector::sharedDirector();
  menu->setPosition(ccp(director->getWinSize().width / 2, 90));
  menu->alignItemsVerticallyWithPadding(20);
  this->addChild(menu);
}

void GameOverLayer::replayButtonPressed(CCObject *sender) {
  _main->getMusic()->stop();
  CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/decide.mp3").c_str());
  CCScene* scene = CCScene::create();
  MainScene* newScene = new MainScene();
  Map* newMap = new Map(_main->getMap()->getIdentifier().c_str());
  newScene->autorelease();
  newScene->init(newMap);
  scene->addChild(newScene);
  newMap->release();
  CCTransitionFade* transition = CCTransitionFade::create(0.5, scene);
  CCDirector::sharedDirector()->replaceScene(transition);
}

void GameOverLayer::titleButtonPressed(CCObject *sender) {
  _main->getMusic()->stop();
  CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/decide.mp3").c_str());
  CCScene* scene = CCScene::create();
  scene->addChild(TitleScene::create());
  CCTransitionFade* transition = CCTransitionFade::create(0.5, scene);
  CCDirector::sharedDirector()->replaceScene(transition);
}