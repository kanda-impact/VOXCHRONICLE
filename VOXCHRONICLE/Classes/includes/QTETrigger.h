//
//  QTETrigger.h
//  VOXCHRONICLE
//
//  Created by giginet on 2013/1/3.
//
//

#ifndef __VOXCHRONICLE__QTETrigger__
#define __VOXCHRONICLE__QTETrigger__

#include <iostream>
#include "cocos2d.h"
#include "EnemyManager.h"

using namespace cocos2d;

class QTETrigger :public CCLayer {
 private:
  EnemyManager* _enemyManager;
  void onButtonPressed(CCObject* sender);
  bool _pressed;
 public:
  QTETrigger(EnemyManager* manager);
  ~QTETrigger();
  bool isButtonPressed();
};

#endif /* defined(__VOXCHRONICLE__QTETrigger__) */
