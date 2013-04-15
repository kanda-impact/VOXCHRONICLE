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
#include "SimpleAudioEngine.h"

using namespace boost;

typedef enum {
  EffectLayerTagTutorial,
  EffectLayerTagCutin,
  EffectLayerTagWait
} EffectLayerTag;

typedef enum {
  EffectLayerZOrderFocus,
  EffectLayerZOrderCutin,
  EffectLayerZOrderDamageLabel,
  EffectLayerZOrderTension,
  EffectLayerZOrderCharacter,
  EffectLayerZOrderWarning,
  EffectLayerZOrderWait,
  EffectLayerZOrderWindow
} EffectLayerZOrder;

static EffectLayer* _shared = NULL;

EffectLayer* EffectLayer::sharedLayer() {
  if (_shared == NULL) {
    _shared = new EffectLayer();
  }
  return _shared;
}

void EffectLayer::purgeEffectLayer() {
  if (_shared) {
    _shared->stopAllActions();
    _shared->unscheduleAllSelectors();
    if (_shared->getParent()) {
      _shared->getParent()->removeChild(_shared, true);
    }
    _shared->release();
    _shared = NULL;
  }
}

EffectLayer::EffectLayer() {
  _tensionEffectLayer = CCSprite::create("tension_effect.png");
  _tensionEffectLayer->retain();
  _characterEffectLayer = CCSprite::create("mode_vox.png");
  _characterEffectLayer->retain();
  _cutinExtention = NULL;
  _focus = NULL;
  this->reloadEffects();
}

void EffectLayer::reloadEffects() {
  CCDirector* director = CCDirector::sharedDirector();
  CCPoint center = ccp(director->getWinSize().width / 2.0f, director->getWinSize().height / 2.0f);
  _tensionEffectLayer->setPosition(center);
  if (!_tensionEffectLayer->getParent()) {
    this->addChild(_tensionEffectLayer, EffectLayerZOrderTension);
  }
  _tensionEffectLayer->setVisible(false);
  CCTextureCache::sharedTextureCache()->addImage("mode_lsk.png"); // テクスチャーを読んでおく
  _characterEffectLayer->setPosition(center);
  if (!_characterEffectLayer->getParent()) {
    this->addChild(_characterEffectLayer, EffectLayerZOrderCharacter);
  }
  
  _characterEffectLayer->setOpacity(50);
  _characterEffectLayer->runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(CCFadeTo::create(1.0f, 25),
                                                                                            CCFadeTo::create(1.0f, 50))));
}

EffectLayer::~EffectLayer() {
  _tensionEffectLayer->release();
  _characterEffectLayer->release();
  if (_focus) {
    _focus->release();
  }
  if (_cutinExtention) {
    _cutinExtention->release();
  }
}

void EffectLayer::addEffectOnEnemy(Enemy *enemy, const char *prefix, int frameCount, CCRect rect) {
  this->addEffectOnEnemy(enemy, prefix, frameCount, rect, 4.0 / 60.0);
}

void EffectLayer::addEffectOnEnemy(Enemy *enemy, const char *prefix, int frameCount, CCRect rect, float delay) {
  CCSprite* effect = CCSprite::create((string(prefix) + string("0.png")).c_str());
  CCAnimation* animation = CCAnimation::create();
  CCPoint position;
  CCDirector* director = CCDirector::sharedDirector();
  if (enemy) {
    position = ccpAdd(enemy->getPosition(), ccp(0, enemy->getContentSize().height * enemy->getCurrentScale(enemy->getRow()) * 0.5f));
    effect->setScale(enemy->getScale() * 4);
  } else {
    position = ccp(director->getWinSize().width / 2.0f, director->getWinSize().height / 2.0f);
    effect->setScale(4.0f);
  }
  effect->setPosition(position);
  for (int i = 0; i < frameCount; ++i) {
    const char* frameName = (string(prefix) + lexical_cast<string>(i) + string(".png")).c_str();
    animation->addSpriteFrame(CCSpriteFrame::create(FileUtils::getFilePath(frameName).c_str(), rect));
  }
  animation->setDelayPerUnit(delay);
  effect->runAction(CCSequence::create(CCAnimate::create(animation),
                                       CCFadeOut::create(0.1f),
                                       CCRemoveFromParentAction::create(),
                                       NULL));
  this->addChild(effect);
}

void EffectLayer::addSkillEffect(Skill *skill, CCArray* targets) {
  // エフェクトを追加する
  CCDirector* director = CCDirector::sharedDirector();
  SkillEffectType effectType = skill->getEffectType();
  int enemyCount = targets->count();
  if (effectType == SkillEffectTypeAll || (effectType == SkillEffectTypeTarget && enemyCount > 0)) {
    int frames = skill->getEffectFrames();
    if (effectType == SkillEffectTypeTarget) { // 1体のみにアニメーションを表示させるとき
      Enemy* target = (Enemy*)targets->objectAtIndex(0);
      this->addEffectOnEnemy(target, skill->getIdentifier().c_str(), frames, CCRectMake(0, 0, 50, 50));
    } else { // 全体にアニメーションを表示させるとき
      CCRect rect = CCRectMake(0, 0, director->getWinSize().width / 4.0, director->getWinSize().height / 4.0);
      this->addEffectOnEnemy(NULL, skill->getIdentifier().c_str(), frames, rect);
    }
  }
}

void EffectLayer::setTensionEffect(int tension) {
  _tensionEffectLayer->stopAllActions();
  if (tension == 0) {
    _tensionEffectLayer->setVisible(false);
  } else {
    _tensionEffectLayer->setVisible(true);
    float delay = (5 - tension) * 0.05;
    _tensionEffectLayer->setOpacity(100);
    CCSequence* blink = CCSequence::createWithTwoActions(CCFadeTo::create(delay, 100),
                                                         CCFadeTo::create(delay, 20));
    _tensionEffectLayer->runAction(CCRepeatForever::create(blink));
  }
}

void EffectLayer::setCharacterEffect(Character *character) {
  if (character->getCharacterType() == CharacterTypeVox) {
    CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("mode_vox.png");
    _characterEffectLayer->setTexture(texture);
  } else {
    CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("mode_lsk.png");
    _characterEffectLayer->setTexture(texture);
  }
}

PopupWindow* EffectLayer::addPopupWindow(int pages) {
  CCAssert(this->getPopupWindow() == NULL, "");
  PopupWindow* window = PopupWindow::create(pages);
  CCDirector* director = CCDirector::sharedDirector();
  window->setPosition(ccp(director->getWinSize().width / 2.0, director->getWinSize().height / 2.0f));
  window->setScale(0);
  window->runAction(CCSequence::create(CCDelayTime::create(0.5f),
                                       CCCallFuncN::create(window, callfuncN_selector(PopupWindow::onPopupStart)),
                                       CCScaleTo::create(0.3f, 1.0),
                                       CCCallFuncN::create(window, callfuncN_selector(PopupWindow::onPopupAppeared)),
                                       NULL));
  this->addChild(window, EffectLayerZOrderWindow, EffectLayerTagTutorial);
  return window;
}

void EffectLayer::addCutin(Skill *skill, EffectLayerCutinType cutinType, float duration) {
  // カットインを追加する
  const int height = 100;
  const float slideTime = duration * 0.0625;
  const float stopTime = duration * 0.375;
  CCSize size = CCDirector::sharedDirector()->getWinSize();
  CCSprite* holdCutin = (CCSprite*)this->getChildByTag(EffectLayerTagCutin);
  if (cutinType == EffectLayerCutinTypeCastOff || holdCutin) {
    if (!holdCutin) return;
    holdCutin->runAction(CCSequence::create(CCMoveTo::create(slideTime, ccp(size.width, height)),
                                            CCRemoveFromParentAction::create(),
                                            NULL));
    if (cutinType == EffectLayerCutinTypeCastOff) {
      return;
    }
  }
  string cutinFile = "Image/" + string(skill->getIdentifier()) + "_icon.png";
  CCSprite* cutin = CCSprite::create(FileUtils::getFilePath(cutinFile.c_str()).c_str());
  if (cutin != NULL) {
    cutin->setPosition(ccp(0, height));
    cutin->setScale(1.0f);
    if (cutinType == EffectLayerCutinTypeNormal) {
      // 通常カットイン
      cutin->runAction(CCSequence::create(CCMoveTo::create(slideTime, ccp(size.width / 2.0, height)),
                                          CCDelayTime::create(stopTime),
                                          CCMoveTo::create(slideTime, ccp(size.width, height)),
                                          CCRemoveFromParentAction::create(),
                                          NULL));
    } else if (cutinType == EffectLayerCutinTypeFailure) {
      // ミスったとき
      cutin->runAction(CCSequence::create(CCMoveTo::create(slideTime, ccp(size.width / 2.0, height)),
                                          CCRotateBy::create(stopTime / 2.0, 45),
                                          CCDelayTime::create(stopTime / 2.0),
                                          CCMoveTo::create(slideTime, ccp(size.width / 2.0, -100)),
                                          CCRemoveFromParentAction::create(),
                                          NULL));
    } else if (cutinType == EffectLayerCutinTypeRegist) {
      // 耐性こうげきしたとき
      cutin->runAction(CCSequence::create(CCMoveTo::create(slideTime, ccp(size.width / 2.0, height)),
                                          CCRepeat::create(CCSequence::create(CCRotateTo::create(stopTime / 6.0, 15),
                                                                              CCRotateTo::create(stopTime / 6.0, -15),
                                                                              NULL), 3),
                                          CCMoveTo::create(slideTime, ccp(size.width, height)),
                                          CCRemoveFromParentAction::create(),
                                          NULL));
    } else if (cutinType == EffectLayerCutinTypeHold) {
      cutin->runAction(CCMoveTo::create(slideTime, ccp(size.width / 2.0, height)));
    }
    if (_cutinExtention) {
      _cutinExtention->setScale(0.5);
      cutin->addChild(_cutinExtention);
    }
    this->addChild(cutin, EffectLayerZOrderCutin, EffectLayerTagCutin);
  }
  this->setCutinExtension(NULL);
}

void EffectLayer::addQTEAttack(Enemy *boss) {
  // QTE用攻撃エフェクト
  // 同じコマをループさせるという特殊なことをしているため、ハードコーディング
  const char* prefix = "qte_attack";
  CCSprite* effect = CCSprite::create((string(prefix) + string("0.png")).c_str());
  CCAnimation* animation = CCAnimation::create();
  CCPoint position = ccpAdd(boss->getPosition(), ccp(0, boss->getContentSize().height * boss->getCurrentScale(boss->getRow()) * 0.5f));
  effect->setScale(boss->getScale());
  effect->setPosition(position);
  CCRect rect = CCRectMake(0, 0, 50, 50);
  for (int i = 0; i < 5; ++i) {
    const char* frameName = (string(prefix) + lexical_cast<string>(i) + string(".png")).c_str();
    animation->addSpriteFrame(CCSpriteFrame::create(FileUtils::getFilePath(frameName).c_str(), rect));
  }
  for (int j = 0; j < 4; ++j) {
    for (int i = 6; i < 13; ++i) {
      const char* frameName = (string(prefix) + lexical_cast<string>(i) + string(".png")).c_str();
      animation->addSpriteFrame(CCSpriteFrame::create(FileUtils::getFilePath(frameName).c_str(), rect));
    }
  }
  animation->setDelayPerUnit(4 / 60.0);
  effect->runAction(CCSequence::create(CCAnimate::create(animation),
                                       CCFadeOut::create(0.1f),
                                       CCRemoveFromParentAction::create(),
                                       NULL));
  effect->setScale(4.0);
  this->addChild(effect);
}

PopupWindow* EffectLayer::getPopupWindow() {
  return (PopupWindow*)this->getChildByTag(EffectLayerTagTutorial);
}

void EffectLayer::addMusicInfo(Map* map, Level* level) {
  // 作曲者情報と曲名を表示する
  MusicSet* mSet = map->getCurrentMusic(level);
  CCNode* musicInfo = CCNode::create();
  CCLabelTTF* nameShadowLabel = CCLabelTTF::create(mSet->getName().c_str(),
                                                   "Helvetica",
                                                   20,
                                                   CCSizeMake(300, 30),
                                                   kCCTextAlignmentRight);
  musicInfo->addChild(nameShadowLabel);
  nameShadowLabel->setColor(ccc3(33, 33, 33));
  nameShadowLabel->setPosition(ccp(2, -2));
  CCLabelTTF* composerShadowLabel = CCLabelTTF::create(mSet->getComposer().c_str(),
                                                       "Helvetica",
                                                       16,
                                                       CCSizeMake(300, 20),
                                                       kCCTextAlignmentRight);
  composerShadowLabel->setColor(ccc3(33, 33, 33));
  composerShadowLabel->setPosition(ccp(2, -27));
  musicInfo->addChild(composerShadowLabel);
  CCLabelTTF* nameLabel = CCLabelTTF::create(mSet->getName().c_str(),
                                             "Helvetica",
                                             20,
                                             CCSizeMake(300, 30),
                                             kCCTextAlignmentRight);
  musicInfo->addChild(nameLabel);
  CCLabelTTF* composerLabel = CCLabelTTF::create(mSet->getComposer().c_str(),
                                                 "Helvetica",
                                                 16,
                                                 CCSizeMake(300, 20),
                                                 kCCTextAlignmentRight);
  composerLabel->setPosition(ccp(0, -25));
  musicInfo->addChild(composerLabel);
  this->addChild(musicInfo);
  musicInfo->setPosition(ccp(700, 40));
  musicInfo->runAction(CCSequence::create(CCDelayTime::create(0.5f),
                                          CCMoveTo::create(0.5f, ccp(310, 40)),
                                          CCDelayTime::create(3.0f),
                                          CCMoveTo::create(0.5f, ccp(700, 40)),
                                          CCRemoveFromParentAction::create(),
                                          NULL));
}

void EffectLayer::addDamageLabel(int damage, int offset, DamageLabelType type) {
  // 被ダメージ表示しちゃう
  CCDirector* director = CCDirector::sharedDirector();
  string filename =this->getDamageLabelName(type);
  CCLabelAtlas* damageLabel = CCLabelAtlas::create(boost::lexical_cast<string>(damage).c_str(),
                                                   filename.c_str(), 50, 150, '0');
  damageLabel->setPosition(ccp(director->getWinSize().width / 2 + 50 * offset, 90 + 20 * offset));
  this->addChild(damageLabel, EffectLayerZOrderDamageLabel);
  damageLabel->setScale(0);
  damageLabel->setAnchorPoint(ccp(0.5, 0.5));
  damageLabel->runAction(CCSequence::create(CCDelayTime::create(0.2 * offset), // 時間ずらそう
                                            CCScaleTo::create(0.1, 1.0),
                                            CCDelayTime::create(0.5),
                                            CCEaseSineIn::create(CCMoveBy::create(0.2, ccp(0, -150))),
                                            CCRemoveFromParentAction::create(),
                                            NULL));
}

void EffectLayer::addDamageLabelOnEnemy(Enemy* enemy, int damage, DamageLabelType type) {
  // ダメージラベル
  CCLabelAtlas* damageLabel = CCLabelAtlas::create(boost::lexical_cast<string>(damage).c_str(),
                                                   FileUtils::getFilePath(this->getDamageLabelName(type).c_str()).c_str(), 50, 150, '0');
  CCSize size = enemy->getContentSize();
  float scale = MAX(enemy->getCurrentScale(enemy->getRow()), 0.4);
  damageLabel->setAnchorPoint(ccp(0.5, 0.5));
  damageLabel->setPosition(ccpAdd(enemy->getPosition(), ccp(0, 50 * scale)));
  damageLabel->setScale(scale);
  this->addChild(damageLabel, EffectLayerZOrderDamageLabel);
  damageLabel->runAction(CCSequence::create(CCFadeIn::create(0.2),
                                            CCDelayTime::create(0.5),
                                            CCFadeOut::create(0.2),
                                            CCRemoveFromParentAction::create(),
                                            NULL));
}

string EffectLayer::getDamageLabelName(DamageLabelType type) {
  switch (type) {
    case DamageLabelTypeAttack:
      return "damage_number.png";
      break;
    case DamageLabelTypeHit:
      return "damage_number_hit.png";
      break;
    case DamageLabelTypeCure:
      return "damage_number_cure.png";
      break;
    case DamageLabelTypeMPCure:
      return "damage_number_MPcure.png";
      break;
    default:
      break;
  }
  return "damage_number.png";
}

void EffectLayer::addWarning(float delay) {
  const float fadeDuration = 0.5f;
  const float animationDuration = 0.1f;
  CCDirector* director = CCDirector::sharedDirector();
  CCNode* node = CCNode::create();
  CCSprite* warning = CCSprite::create("warning0.png");
  CCArray* frames = CCArray::create();
  frames->addObject(CCSpriteFrame::create("warning0.png", CCRectMake(0, 0, 480, 123)));
  frames->addObject(CCSpriteFrame::create("warning1.png", CCRectMake(0, 0, 480, 123)));
  CCAnimation* animation = CCAnimation::createWithSpriteFrames(frames);
  animation->setDelayPerUnit(animationDuration);
  animation->setLoops((delay / animation->getDelayPerUnit()) / 2);
  warning->setOpacity(0);
  warning->runAction(CCSequence::create(CCFadeIn::create(fadeDuration),
                                        CCAnimate::create(animation),
                                        CCFadeOut::create(fadeDuration),
                                        NULL));
  CCSprite* band0 = CCSprite::create("warning2.png");
  band0->setPosition(ccp(240, 56));
  band0->runAction(CCMoveBy::create(delay, ccp(-480, 0)));
  
  band0->runAction(CCSequence::create(CCFadeIn::create(fadeDuration),
                                      CCDelayTime::create(delay),
                                      CCFadeOut::create(fadeDuration),
                                      NULL));
  
  CCSprite* band1 = CCSprite::create("warning2.png");
  band1->setPosition(ccp(-240, -56));
  band1->runAction(CCMoveBy::create(delay, ccp(480, 0)));
  band1->runAction(CCSequence::create(CCFadeIn::create(fadeDuration),
                                      CCDelayTime::create(delay),
                                      CCFadeOut::create(fadeDuration),
                                      NULL));
  node->addChild(warning);
  node->addChild(band0);
  node->addChild(band1);
  node->runAction(CCSequence::create(CCDelayTime::create(delay * 2),
                                     CCRemoveFromParentAction::create(), NULL));
  node->setPosition(ccp(director->getWinSize().width / 2.0, 180));
  this->addChild(node, EffectLayerZOrderWarning);
}

void EffectLayer::setCutinExtension(CCNode* extension) {
  if (_cutinExtention) {
    _cutinExtention->release();
  }
  _cutinExtention = extension;
  if (extension) {
    extension->retain();
  }
}

void EffectLayer::reloadFocus(Skin *skin) {
  string focusName = string("Image/") + skin->getPrefix() + string("_focus.png");
  if (_focus) {
    _focus->setTexture(CCTextureCache::sharedTextureCache()->addImage(focusName.c_str()));
  } else {
    _focus = CCSprite::create(FileUtils::getFilePath(focusName.c_str()).c_str());
    _focus->retain();
    this->addChild(_focus, EffectLayerZOrderFocus);
  }
  _focus->setVisible(false);
  _focus->setAnchorPoint(ccp(0.5f, 0.0f));
}

void EffectLayer::updateFocus(EnemyManager *manager) {
  Enemy* nearest = manager->getNearestEnemy();
  if (nearest) {
    _focus->setVisible(true);
    _focus->setPosition(ccpAdd(nearest->getPosition(), ccp(0, nearest->getContentSize().height * nearest->getCurrentScale(nearest->getRow()) * 0.8)));
    _focus->setScale(MAX(nearest->getCurrentScale(nearest->getRow()), 0.4));
  } else {
    _focus->setVisible(false);
  }
}

void EffectLayer::addWaitMarker(float duration) {
  if (!this->getChildByTag(EffectLayerTagWait)) {
    CCDirector* director = CCDirector::sharedDirector();
    CCSprite* wait = CCSprite::create("wait_front.png");
    //CCSprite* marker = CCSprite::create("wait_back.png");
    wait->setOpacity(0);
    wait->runAction(CCSequence::create(CCFadeIn::create(0.25f),
                                       CCDelayTime::create(duration - 0.5f),
                                       CCFadeOut::create(0.25f),
                                       CCRemoveFromParentAction::create(),
                                       NULL));
    wait->setPosition(ccp(director->getWinSize().width / 2.0f, director->getWinSize().height / 2.0f));
    this->addChild(wait, EffectLayerZOrderWait);
  }
}