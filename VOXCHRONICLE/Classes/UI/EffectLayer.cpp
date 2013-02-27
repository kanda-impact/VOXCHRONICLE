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
#include "CCRemoveFromParentAction.h"

using namespace boost;

static EffectLayer* _shared = NULL;

EffectLayer* EffectLayer::sharedLayer() {
  if (!_shared) {
    _shared = new EffectLayer();
  }
  return _shared;
}

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
    effect->runAction(CCSequence::create(CCAnimate::create(animation),
                                         CCFadeOut::create(0.1f),
                                         CCRemoveFromParentAction::create(),
                                         NULL));
    this->addChild(effect);
  }
}

void EffectLayer::addTutorialWindow() {
}

void EffectLayer::addCutin(Skill *skill, bool succeed, float duration) {
  // カットインを追加する
  string cutinFile = "Image/" + string(skill->getIdentifier()) + "_icon.png";
  CCSprite* cutin = CCSprite::create(FileUtils::getFilePath(cutinFile.c_str()).c_str());
  if (cutin != NULL) {
    const int height = 100;
    cutin->setPosition(ccp(0, height));
    cutin->setScale(0.5);
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    if (succeed) {
      // 成功したとき、カットインを挿入
      cutin->runAction(CCSequence::create(CCMoveTo::create(duration * 0.125, ccp(size.width / 2.0, height)),
                                          CCDelayTime::create(duration * 0.25),
                                          CCMoveTo::create(duration * 0.125, ccp(size.width, height)),
                                          CCRemoveFromParentAction::create(),
                                          NULL));
    } else {
      // ミスったとき、コマンドを落とす
      cutin->runAction(CCSequence::create(CCMoveTo::create(duration * 0.125, ccp(size.width / 2.0, height)),
                                          CCRotateBy::create(duration * 0.125, 45),
                                          CCDelayTime::create(duration * 0.125),
                                          CCMoveTo::create(duration * 0.125, ccp(size.width / 2.0, -100)),
                                          CCRemoveFromParentAction::create(),
                                          NULL));
    }
    this->addChild(cutin);
  }
}