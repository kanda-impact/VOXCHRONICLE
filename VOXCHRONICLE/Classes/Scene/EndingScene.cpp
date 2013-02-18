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
  CCLabelTTF* label = CCLabelTTF::create(text.c_str(),
                                         "Helvetica",
                                         16,
                                         CCSizeMake(director->getWinSize().width, director->getWinSize().height * 2),
                                         kCCTextAlignmentLeft,
                                         kCCVerticalTextAlignmentTop);
  string backgroundImage = obj->getString("background");
  if (backgroundImage.length() > 0) {
    CCSprite* sprite = CCSprite::create(backgroundImage.c_str());
    sprite->setPosition(ccp(director->getWinSize().width / 2.0f, director->getWinSize().height / 2.0f));
    this->addChild(sprite);
  }
  label->setPosition(ccp(director->getWinSize().width / 2.0f, - director->getWinSize().height));
  label->runAction(CCMoveBy::create(10.0f, ccp(0, director->getWinSize().height)));
}

EndingScene::~EndingScene() {
}

void EndingScene::registerWithTouchDispatcher() {
  CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool EndingScene::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent) {
  CCScene* scene = CCScene::create();
  scene->addChild(TitleScene::create());
  CCTransitionCrossFade* fade = CCTransitionCrossFade::create(1.0f, scene);
  CCDirector::sharedDirector()->replaceScene(fade);
  return true;
}
