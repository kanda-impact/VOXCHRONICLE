//
//  EffectLayer.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/2/27.
//
//

#include "EffectLayer.h"
#include "FileUtils.h"
#include <boost/lexical_cast.hpp>

using namespace boost;

EffectLayer::EffectLayer() {
}

EffectLayer::~EffectLayer() {
}

void EffectLayer::addSkillEffect(Skill *skill, CCArray* targets) {
  // エフェクトを追加する
  CCDirector* director = CCDirector::sharedDirector();
  SkillEffectType effectType = skill->getEffectType();
  int enemyCount = targets->count();
  if (effectType == SkillEffectTypeAll || (effectType == SkillEffectTypeTarget && enemyCount > 0)) {
    int frames = skill->getEffectFrames();
    CCSprite* effect = CCSprite::create((string(skill->getIdentifier()) + string("0.png")).c_str());
    CCAnimation* animation = CCAnimation::create();
    CCRect rect;
    if (effectType == SkillEffectTypeTarget) { // 1体のみにアニメーションを表示させるとき
      Enemy* target = (Enemy*)targets->objectAtIndex(0);
      CCPoint position = ccpAdd(target->getPosition(), ccp(0, target->getContentSize().height * target->getCurrentScale(target->getRow()) * 0.5f));
      rect = CCRectMake(0, 0, 200, 200);
      effect->setPosition(position);
      effect->setScale(target->getScale());
    } else { // 全体にアニメーションを表示させるとき
      CCPoint position = ccp(director->getWinSize().width / 2.0, director->getWinSize().height / 2.0);
      rect = CCRectMake(0, 0, director->getWinSize().width, director->getWinSize().height);
      effect->setPosition(position);
    }
    for (int i = 0; i < frames; ++i) {
      const char* frameName = (string(skill->getIdentifier()) + lexical_cast<string>(i) + string(".png")).c_str();
      animation->addSpriteFrame(CCSpriteFrame::create(FileUtils::getFilePath(frameName).c_str(), rect));
    }
    animation->setDelayPerUnit(2.0 / 60.0);
    /*effect->runAction(CCSequence::create(CCAnimate::create(animation),
                                         CCFadeOut::create(0.1f),
                                         CCCallFuncN::create(this, callfuncN_selector(MainScene::removeNode)),
                                         NULL));*/
    this->addChild(effect);
  }
}

void EffectLayer::addTutorialWindow() {
}

void EffectLayer::addCutin(Skill *skill) {
}