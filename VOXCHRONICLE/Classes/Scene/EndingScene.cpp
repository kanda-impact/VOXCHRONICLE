//
//  EndingScene.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/2/18.
//
//

#include "EndingScene.h"
#include "LuaObject.h"
#include "TitleScene.h"

EndingScene::EndingScene(const char* endingScript) {
  LuaObject* obj = LuaObject::create(endingScript);

  CCDirector* director = CCDirector::sharedDirector();
  string text = obj->getString("text");
  _musicDuration = obj->getInt("duration");
  _music = obj->getString("music");
  CCLabelTTF* label = CCLabelTTF::create(text.c_str(),
                                         "Helvetica",
                                         24,
                                         CCSizeMake(director->getWinSize().width, director->getWinSize().height * 2),
                                         kCCTextAlignmentLeft,
                                         kCCVerticalTextAlignmentCenter);
  label->setColor(ccc3(255, 255, 255));
  string backgroundImage = obj->getString("background");
  if (backgroundImage.length() > 0) {
    CCSprite* sprite = CCSprite::create(backgroundImage.c_str());
    sprite->setPosition(ccp(director->getWinSize().width / 2.0f, director->getWinSize().height / 2.0f));
    this->addChild(sprite);
  }
  label->setPosition(ccp(director->getWinSize().width / 2.0f, - director->getWinSize().height));
  this->addChild(label);
  label->runAction(CCSequence::create(CCMoveTo::create(15.0f, ccp(director->getWinSize().width / 2.0f, director->getWinSize().height /2.0f)),
                                      CCDelayTime::create(6.0f),
                                      NULL));
}

EndingScene::~EndingScene() {
}

void EndingScene::goToNextScene(cocos2d::CCObject *sender) {
  CCScene* scene = CCScene::create();
  scene->addChild(TitleScene::create());
  CCTransitionFade* fade = CCTransitionFade::create(2.0f, scene);
  CCDirector::sharedDirector()->replaceScene(fade);
}

void EndingScene::onEnterTransitionDidFinish() {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(_music.c_str(), false);
  this->getScheduler()->scheduleSelector(schedule_selector(EndingScene::goToNextScene), this, 0, false, 0, _musicDuration);
}