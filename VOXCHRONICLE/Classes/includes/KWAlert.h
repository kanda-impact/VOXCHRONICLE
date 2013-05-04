//
//  KWAlert.h
//  VOXCHRONICLE
//
//  Created by giginet on 2013/4/30.
//
//

#ifndef __VOXCHRONICLE__KWAlert__
#define __VOXCHRONICLE__KWAlert__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class KWAlertDelegate;

class KWAlert :public CCSprite {
 private:
  CCLabelTTF* _label;
  KWAlertDelegate* _delegate;
  CCMenu* _menu;
  void onButtonPressed(CCObject* sender);
 public:
  KWAlert(const char* background, CCArray* buttonNames);
  virtual ~KWAlert();
  void show();
  void dismiss();
  void setText(const char* text);
  KWAlertDelegate* getDelegate();
  void setDelegate(KWAlertDelegate* delegate);
  void setEnabled(bool enable);
};

#endif /* defined(__VOXCHRONICLE__KWAlert__) */
