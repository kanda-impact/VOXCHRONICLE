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
  CCLabelTTF* gameOverLabel = CCLabelTTF::create("GAME OVER", FONT_NAME, 48);
  CCDirector* director = CCDirector::sharedDirector();
  CCPoint center = CCPointMake(director->getWinSize().width / 2, director->getWinSize().height / 2);
  CCLabelTTF* gameOverShadowLavel = CCLabelTTF::create("GAME OVER", FONT_NAME, 48);
  gameOverShadowLavel->setColor(ccc3(64, 64, 64));
  gameOverShadowLavel->setPosition(center);
  gameOverLabel->setPosition(ccpAdd(ccp(gameOverShadowLavel->getContentSize().width / 2, gameOverShadowLavel->getContentSize().height / 2), ccp(-3, 3)));
  this->addChild(gameOverShadowLavel);
  gameOverShadowLavel->addChild(gameOverLabel);
  gameOverShadowLavel->runAction(CCSequence::create(CCDelayTime::create(3.0),
                                                    CCMoveTo::create(0.1, ccp(director->getWinSize().width / 2, 200)),
                                                    CCCallFunc::create(this, callfunc_selector(GameOverLayer::addGameOverButtons)),
                                                    NULL));
}

void GameOverLayer::addGameOverButtons() {
  CCLabelTTF* replayLabel = CCLabelTTF::create("リプレイ", "", 24);
  CCLabelTTF* titleLabel = CCLabelTTF::create("タイトル", FONT_NAME, 24);
  CCMenu* menu = CCMenu::create(CCMenuItemLabel::create(replayLabel, this, menu_selector(GameOverLayer::replayButtonPressed)),
                                CCMenuItemLabel::create(titleLabel, this, menu_selector(GameOverLayer::titleButtonPressed)),
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