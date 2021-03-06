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

EndingScene::EndingScene(const char* endingScript) {
  LuaObject* obj = LuaObject::create(endingScript);
  CCDirector* director = CCDirector::sharedDirector();
  
  _identifier = endingScript;
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
  this->setTouchEnabled(true);
  
  _achievementId = obj->getString("achievement");
}

EndingScene::~EndingScene() {
}

void EndingScene::goToNextScene(cocos2d::CCObject *sender) {
  // 実績解除
  SaveData::sharedData()->unlockAchievement(_achievementId.c_str());
  
  CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
  CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
  CCScene* scene = CCScene::create();
  PlayLog* log = (PlayLog*)this->getUserObject();
  StaffRollScene* layer = new StaffRollScene(log->getMapHistory());
  layer->setUserObject(this->getUserObject());
  layer->autorelease();
  scene->addChild(layer);
  CCTransitionFade* fade = CCTransitionFade::create(0.5f, scene);
  CCDirector::sharedDirector()->replaceScene(fade);
}

void EndingScene::onEnterTransitionDidFinish() {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(_music.c_str(), false);
  if (SaveData::sharedData()->isFullVoice()) { // フルボイスモード！
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.4f);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect((_identifier + "_voice.mp3").c_str());
  }
  this->getScheduler()->scheduleSelector(schedule_selector(EndingScene::goToNextScene), this, 0, false, 0, _musicDuration);
  CCDirector* director = CCDirector::sharedDirector();
  CCLayer* bg = (CCLayer*)this->getChildByTag(EndingSceneTagShadowBackground);
  bg->runAction(CCSequence::create(CCDelayTime::create(_musicDuration - 3.0f),
                                   CCFadeTo::create(0.5f, 0),
                                   CCRemoveFromParentAction::create(), NULL));
  CCLayer* labels = (CCLayer*)bg->getChildByTag(EndingSceneTagLabel);
  labels->runAction(CCMoveTo::create(12.0f, ccp(director->getWinSize().width / 2.0f, director->getWinSize().height /2.0f)));
  
  // TestFlight用のログを生成
#if TESTING
  PlayLog* log = (PlayLog*)this->getUserObject();
  CCObject* obj = NULL;
  stringstream ss;
  CCARRAY_FOREACH(log->getMapHistory(), obj) {
    CCString* map = (CCString*)obj;
    ss << map->getCString() << " ";
  }
  ss << endl;
  ss << "death = " << log->getCount(PlayLogKeyDead) << endl;
  ss << "hit = " << log->getCount(PlayLogKeyHitDamage) << endl;
  ss << "defeat = " << log->getCount(PlayLogKeyMaxDefeat) << endl;
  ss << "turn = " << log->getCount(PlayLogKeyTurn) << endl;
  CCLog("%s", ss.str().c_str());
  Kawaz::TestFlightWrapper::submitFeedback(ss.str().c_str());
#endif
}

void EndingScene::registerWithTouchDispatcher() {
  CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 100, true);
}
 
bool EndingScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
  CCLayer* bg = (CCLayer*)this->getChildByTag(EndingSceneTagShadowBackground);
  if (bg) {
    CCLayer* labels = (CCLayer*)bg->getChildByTag(EndingSceneTagLabel);
    if (labels->numberOfRunningActions() > 0) { // ラベルまだ動いてる
      labels->stopAllActions();
      CCDirector* director = CCDirector::sharedDirector();
      labels->setPosition(ccp(director->getWinSize().width / 2.0f, director->getWinSize().height /2.0f));
    } else { // もう止まってたら
      bg->stopAllActions();
      this->removeChild(bg, true);
    }
  } else { // 背景がもう消えてたら
    this->goToNextScene(this);
  }
  return true;
}

