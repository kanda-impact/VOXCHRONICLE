//
//  BlinkLayer.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/10/27.
//
//

#include "BlinkLayer.h"

BlinkLayer::BlinkLayer(ccColor4B color) {
  CCLayerColor* layer = CCLayerColor::create(color);
  layer->runAction(CCSequence::create(CCRepeat::create(CCSequence::create(CCFadeTo::create(0.05, 64),
                                                       CCFadeTo::create(0.05, 128),
                                                       NULL), 3),
                   CCCallFunc::create(this, callfunc_selector(BlinkLayer::removeFromParentAndCleanup)),
                   NULL));
  this->addChild(layer);
}