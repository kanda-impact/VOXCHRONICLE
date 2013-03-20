//
//  BlinkLayer.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/10/27.
//
//

#include "BlinkLayer.h"

BlinkLayer::BlinkLayer(ccColor4B color, float delay) {
  CCLayerColor* layer = CCLayerColor::create(color);
  layer->runAction(CCSequence::create(CCRepeat::create(CCSequence::create(CCFadeTo::create(delay, 64),
                                                       CCFadeTo::create(delay, 128),
                                                       NULL), 3),
                   CCCallFunc::create(this, callfunc_selector(BlinkLayer::suicide)),
                   NULL));
  this->addChild(layer);
}

void BlinkLayer::suicide() {
  this->removeFromParentAndCleanup(true);
}