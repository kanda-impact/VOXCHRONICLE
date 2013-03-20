//
//  DictionaryScene.h
//  VOXCHRONICLE
//
//  Created by giginet on 2013/3/18.
//
//

#ifndef __VOXCHRONICLE__DictionaryScene__
#define __VOXCHRONICLE__DictionaryScene__

#include <iostream>
#include "cocos2d.h"
#include "Enemy.h"

using namespace cocos2d;

class DictionaryScene :public CCLayer {
 private:
  void loadEnemyByIndex(int idx);
  void onCursorButtonPressed(CCObject* sender);
  void onBackButtonPressed(CCObject* sender);
  int _cursor;
  Enemy* _enemy;
  CCArray* _enemies;
  CCLabelTTF* _nameLabel;
  CCLabelTTF* _habitatLabel;
  CCLabelTTF* _descriptionLabel;
 public:
  virtual bool init();
  virtual ~DictionaryScene();
  CREATE_FUNC(DictionaryScene);
};

#endif /* defined(__VOXCHRONICLE__DictionaryScene__) */
