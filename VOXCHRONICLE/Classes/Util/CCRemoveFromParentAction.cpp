//
//  CCRemoveFromParentAction.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/2/27.
//
//

#include "CCRemoveFromParentAction.h"

void CCRemoveFromParentAction::startWithTarget(cocos2d::CCNode *pTarget) {
  CCActionInstant::startWithTarget(pTarget);
  pTarget->removeFromParentAndCleanup(true);
}