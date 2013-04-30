//
//  EffectLayer.h
//  VOXCHRONICLE
//
//  Created by giginet on 2013/2/27.
//
//

#ifndef __VOXCHRONICLE__EffectLayer__
#define __VOXCHRONICLE__EffectLayer__

#include <iostream>
#include "cocos2d.h"
#include "Skill.h"
#include "EnemyManager.h"
#include "PopupWindow.h"
#include "Map.h"

using namespace cocos2d;

/**
 画面中のエフェクトを追加するCCLayer
 スクリプトから叩きやすいようにシングルトンになっている
 */

typedef enum {
  EffectLayerCutinTypeNormal,
  EffectLayerCutinTypeFailure,
  EffectLayerCutinTypeHold,
  EffectLayerCutinTypeCastOff,
  EffectLayerCutinTypeRegist
} EffectLayerCutinType;

typedef enum {
  DamageLabelTypeAttack,
  DamageLabelTypeHit,
  DamageLabelTypeCure,
  DamageLabelTypeMPCure
} DamageLabelType;

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
  EffectLayerZOrderMessage,
  EffectLayerZOrderWait,
  EffectLayerZOrderWindow
} EffectLayerZOrder;

class EffectLayer :public CCLayer {
 private:
  CCSprite* _tensionEffectLayer;
  CCSprite* _characterEffectLayer;
  string getDamageLabelName(DamageLabelType type);
  CCNode* _cutinExtention;
  CCSprite* _focus;
 public:
  static EffectLayer* sharedLayer();
  static void purgeEffectLayer();
  EffectLayer();
  ~EffectLayer();
  void addEffectOnEnemy(Enemy* enemy, const char* prefix, int frameCount, CCRect rect);
  void addEffectOnEnemy(Enemy* enemy, const char* prefix, int frameCount, CCRect rect, float delay);
  void addMusicInfo(Map* map, Level* level);
  void addDamageLabel(int damage, int offset, DamageLabelType type);
  void addDamageLabelOnEnemy(Enemy* enemy, int damage, DamageLabelType type);
  void addSkillEffect(Skill* skill, CCArray* targets);
  void setTensionEffect(int tension);
  void setCharacterEffect(Character* character);
  PopupWindow* addPopupWindow(int pages);
  PopupWindow* getPopupWindow();
  void addCutin(Skill *skill, EffectLayerCutinType cutinType, float duration);
  void addQTEAttack(Enemy* boss);
  void reloadEffects();
  void addWarning(float delay);
  void setCutinExtension(CCNode* extension);
  void reloadFocus(Skin* skin);
  void updateFocus(EnemyManager* manager);
  void addWaitMarker(float duration);
};

#endif /* defined(__VOXCHRONICLE__EffectLayer__) */
