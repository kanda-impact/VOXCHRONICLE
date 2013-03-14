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
  
  CCMenuItemSprite* easyButton = CCMenuItemSprite::create(this->buttonNode("easy", "simple_thumbnail.png", false),
                                                          this->buttonNode("easy", "simple_thumbnail.png", true),
                                                          this,
                                                          menu_selector(SelectScene::onEasyButtonPressed));
  
  CCMenuItemSprite* hardButton = CCMenuItemSprite::create(this->buttonNode("hard", "simple_thumbnail.png", false),
                                                          this->buttonNode("hard", "simple_thumbnail.png", true),
                                                          this,
                                                          menu_selector(SelectScene::onHardButtonPressed));
  CCMenu* mainMenu = CCMenu::create(easyButton, hardButton, NULL);
  mainMenu->alignItemsHorizontallyWithPadding(105);
  mainMenu->setAnchorPoint(ccp(0.5, 0.5));
  
  mainMenu->setPosition(ccp(director->getWinSize().width / 2.0 + 2, 127));
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
  
  CCSprite* easyFrame = CCSprite::create("select_easy_frame.png");
  easyFrame->setPosition(ccp(134, 140));
  this->addChild(easyFrame);

  CCSprite* hardFrame = CCSprite::create("select_hard_frame.png");
  hardFrame->setPosition(ccp(350, 140));
  this->addChild(hardFrame);
  
  this->createThumbnails();
  
  return true;
}

SelectScene::SelectScene() {
}

SelectScene::~SelectScene() {
  _thumbnails->release();
}

CCNode* SelectScene::buttonNode(const char *key, const char* thumbnail, bool pressed) {
  CCNode* node = CCNode::create();
  if (string(thumbnail).length() > 0) {
    CCSprite* thumbnailSprite = CCSprite::create(thumbnail);
    thumbnailSprite->setPosition(ccp(82, 120));
    node->addChild(thumbnailSprite);
  }
  CCSprite* window = CCSprite::create("select_window.png");
  node->addChild(window);
  window->setPosition(ccp(82, 92));
  stringstream ss;
  ss << "select_" << key;
  if (pressed) {
    ss << "_pressed";
  }
  ss << ".png";
  CCSprite* label = CCSprite::create(ss.str().c_str());
  label->setPosition(ccp(82, 50));
  node->addChild(label);
  node->setContentSize(window->getTextureRect().size);
  return node;
}

void SelectScene::createThumbnails() {
  const int x[] = {190, 240, 290, 165, 215, 265, 315};
  const int y[] = {262, 262, 262, 303, 303, 303, 303};
  // マップによって切り替えたり、セーブデータによって切り替えたりはあとで実装する
  for (int i = 0; i < 7; ++i) {
    CCSprite* sprite = CCSprite::create("castle_icon.png");
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