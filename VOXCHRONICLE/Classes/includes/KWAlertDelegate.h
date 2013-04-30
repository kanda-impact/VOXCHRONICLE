//
//  KWAlertDelegate.h
//  VOXCHRONICLE
//
//  Created by giginet on 2013/4/30.
//
//

#ifndef __VOXCHRONICLE__KWAlertDelegate__
#define __VOXCHRONICLE__KWAlertDelegate__

#include <iostream>
#include "cocos2d.h"

#include "KWAlert.h"

using namespace cocos2d;

class KWAlertDelegate {
 public:
  virtual void clickedButtonAtIndex(KWAlert* alert, int index);
  virtual void didPresentAlert(KWAlert* alert);
};

#endif /* defined(__VOXCHRONICLE__KWAlertDelegate__) */
