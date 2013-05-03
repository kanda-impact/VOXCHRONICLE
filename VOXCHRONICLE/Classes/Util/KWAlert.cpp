//
//  KWAlert.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/4/30.
//
//

#include "KWAlert.h"
#include "KWAlertDelegate.h"
#include "CCRemoveFromParentAction.h"

KWAlertDelegate* KWAlert::getDelegate() {
  return _delegate;
}

void KWAlert::setDelegate(KWAlertDelegate *delegate) {
  _delegate = delegate; // weak
}

KWAlert::KWAlert(const char* background, CCArray* buttonNames) {
  if (this->initWithFile(background)) {
    this->setScale(0);
    _delegate = NULL;
    CCArray* items = CCArray::create();
    CCObject* obj = NULL;
    int i = 0;
    CCARRAY_FOREACH(buttonNames, obj) {
      CCString* name = (CCString*)obj;
      CCMenuItemImage* image = CCMenuItemImage::create("free.png", "free_pressed.png", this, menu_selector(KWAlert::onButtonPressed));
      CCLabelTTF* label = CCLabelTTF::create(name->getCString(), "Helvetica", 24);
      image->setTag(i);
      image->addChild(label);
      label->setPosition(ccp(62.5, 20));
      items->addObject(image);
      ++i;
    }
    CCMenu* menu = CCMenu::createWithArray(items);
    menu->setPosition(ccp(200, 40));
    menu->alignItemsHorizontallyWithPadding(40);
    this->addChild(menu);
    _label = CCLabelTTF::create("", "Helvetica", 16, CCSizeMake(380, 180), kCCTextAlignmentCenter, kCCVerticalTextAlignmentTop);
    _label->retain();
    _label->setPosition(ccp(200, 50));
    this->addChild(_label);
  }
}

void KWAlert::onButtonPressed(cocos2d::CCObject *sender) {
  int idx = ((CCNode*)sender)->getTag();
  if (_delegate) {
    _delegate->clickedButtonAtIndex(this, idx);
  }
}

void KWAlert::show() {
  this->runAction(CCScaleTo::create(0.2, 1.0));
}

void KWAlert::dismiss() {
  this->runAction(CCSequence::create(CCScaleTo::create(0.2, 0),
                                     CCRemoveFromParentAction::create(),
                                     NULL));
}

KWAlert::~KWAlert() {
  _label->release();
}

void KWAlert::setText(const char *text) {
  _label->setString(text);
}