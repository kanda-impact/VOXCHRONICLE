//
//  CCRemoveFromParentAction.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/2/27.
//
//

#include "CCRemoveFromParentAction.h"

CCRemoveFromParentAction* CCRemoveFromParentAction::create() {
  CCRemoveFromParentAction *pRet = new CCRemoveFromParentAction();
  
  if (pRet) {
    pRet->autorelease();
    return pRet;
  }
  
  CC_SAFE_DELETE(pRet);
  return NULL;
}

void CCRemoveFromParentAction::update(float time) {
  CC_UNUSED_PARAM(time);
  m_pTarget->removeFromParentAndCleanup(true);
}