//
//  EndingScene.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/2/18.
//
//

#include "CCRemoveFromParentAction.h"

#include "EndingScene.h"
#include "LuaObject.h"
#include "TitleScene.h"
#include "StaffRollScene.h"
#include "Map.h"
#include "PlayLog.h"

#include "TestFlightWrapper.h"

#include <sstream>

typedef enum {
  EndingSceneTagLabel,
  EndingSceneTagShadowBackground
} EndingSceneTag;

EndingScene::EndingScene(const char* endingScript, CCArray* maps) {
  _maps = maps;
  maps->retain();
  LuaObject* obj = LuaObject::create(endingScript);
  CCDirector* director = CCDirector::sharedDirector();
  
  string text = obj->getString("text");
  _musicDuration = obj->getInt("duration");
  _music = obj->getString("music");
  CCLabelTTF* label = CCLabelTTF::create(text.c_str(),
                                         "Helvetica",
                                         21,
                                         CCSizeMake(director->getWinSize().width - 50, director->getWinSize().height * 2),
                                         kCCTextAlignmentCenter,
                                         kCCVerticalTextAlignmentCenter);
  CCLabelTTF* shadowLabel = CCLabelTTF::create(text.c_str(),
                                               "Helvetica",
                                               21,
                                               CCSizeMake(director->getWinSize().width - 50, director->getWinSize().height * 2),
                                               kCCTextAlignmentCenter,
                                               kCCVerticalTextAlignmentCenter);
  
  label->setColor(ccc3(255, 255, 255));
  shadowLabel->setColor(ccc3(33, 33, 33));
  shadowLabel->setPosition(ccpAdd(label->getPosition(), ccp(2, -2)));
  string backgroundImage = obj->getString("background");
  if (backgroundImage.length() > 0) {
    CCSprite* sprite = CCSprite::create(backgroundImage.c_str());
    sprite->setPosition(ccp(director->getWinSize().width / 2.0f, director->getWinSize().height / 2.0f));
    this->addChild(sprite);
  }
  
  CCLayerColor* bg = CCLayerColor::create(ccc4(100, 100, 100, 128), director->getWinSize().width, director->getWinSize().height);
  this->addChild(bg, 0, EndingSceneTagShadowBackground);
  CCLayer* labels = CCLayer::create();
  
  labels->addChild(shadowLabel);
  labels->setPosition(ccp(director->getWinSize().width / 2.0f, - director->getWinSize().height / 2.0f));
  labels->addChild(label);
  bg->addChild(labels, 0, EndingSceneTagLabel);
  
  // TestFlight用のログを生成
#if TESTING
  PlayLog* log = (PlayLog*)this->getUserObject();
  CCObject* it = NULL;
  stringstream ss;
  CCARRAY_FOREACH(maps, it) {
    Map* map = (Map*)obj;
    ss << map->getName() << " ";
  }
  ss << endl;
  ss << "death = " << log->getCount(PlayLogKeyDead) << endl;
  ss << "hit = " << log->getCount(PlayLogKeyHitDamage) << endl;
  ss << "defeat = " << log->getCount(PlayLogKeyMaxDefeat) << endl;
  ss << "turn = " << log->getCount(PlayLogKeyTurn) << endl;

  TestFlightWrapper::TestFlightWrapper::submitFeedback(ss.str().c_str());
#endif
  
}

EndingScene::~EndingScene() {
  _maps->release();
}

void EndingScene::goToNextScene(cocos2d::CCObject *sender) {
  CCScene* scene = CCScene::create();
  StaffRollScene* layer = new StaffRollScene(_maps);
  layer->setUserObject(this->getUserObject());
  layer->autorelease();
  scene->addChild(layer);
  CCTransitionFade* fade = CCTransitionFade::create(0.5f, scene);
  CCDirector::sharedDirector()->replaceScene(fade);
}

void EndingScene::onEnterTransitionDidFinish() {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(_music.c_str(), false);
  this->getScheduler()->scheduleSelector(schedule_selector(EndingScene::goToNextScene), this, 0, false, 0, _musicDuration);
  CCDirector* director = CCDirector::sharedDirector();
  CCLayer* bg = (CCLayer*)this->getChildByTag(EndingSceneTagShadowBackground);
  bg->runAction(CCSequence::create(CCDelayTime::create(18.0f),
                                   CCRemoveFromParentAction::create(), NULL));
  CCLayer* labels = (CCLayer*)bg->getChildByTag(EndingSceneTagLabel);
  labels->runAction(CCMoveTo::create(12.0f, ccp(director->getWinSize().width / 2.0f, director->getWinSize().height /2.0f)));
  
}