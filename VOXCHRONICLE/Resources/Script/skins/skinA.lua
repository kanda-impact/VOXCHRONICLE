Skin = {
  name = "SkinA",
  prefix = "cyber",
  hasBackground = false,
  groundFrameCount = 4,
  frameType = ControllerFrameTypeNone,
  buildSkin = function(self)
    -- ここでスキンの定義をｇｄｇｄ書きます
    local hpLabel = CCSprite:createWithSpriteFrameName("cyber_hp.png")
    hpLabel:setPosition(ccp(20, 300));
    self:addChild(hpLabel)
    
    local mpLabel = CCSprite:createWithSpriteFrameName("cyber_mp.png");
    mpLabel:setPosition(ccp(282, 300))
    self:addChild(mpLabel)
  
    local currentHPLabel = CCLabelAtlas:create("0", "cyber_hp_numbers.png", 17, 18, string.byte("0"))
    currentHPLabel:setScale(0.6)
    currentHPLabel:setPosition(ccp(49, 293))
    currentHPLabel:setAnchorPoint(ccp(0.5, 0.5))
  
    local maxHPLabel = CCLabelAtlas:create("0", "cyber_hp_numbers.png", 17, 18, string.byte("0"))
    maxHPLabel:setScale(0.4)
    maxHPLabel:setPosition(ccp(85, 290))
    maxHPLabel:setAnchorPoint(ccp(0.5, 0.5))
    self:addChild(currentHPLabel, 0, CurrentHPLabelTag)
    self:addChild(maxHPLabel, 0, MaxHPLabelTag)
    
    -- MPMarker
    local mpMarker = CCNode:create()
    mpMarker:setPosition(ccp(305, 300))
    self:addChild(mpMarker, 0, MPMarkerTag)
  
    local slash = CCSprite:createWithSpriteFrameName("cyber_slash.png")
    slash:setPosition(ccp(71, 293))
    self:addChild(slash)
  
    local stageLabel = CCSprite:createWithSpriteFrameName("cyber_level.png")
    stageLabel:setPosition(ccp(240, 282))
    self:addChild(stageLabel)
  
    local levelLabel = CCLabelAtlas:create("10", "cyber_level_numbers.png", 18, 23, string.byte("0"))
    levelLabel:setPosition(ccp(222, 290))
    self:addChild(levelLabel, 0, LevelLabelTag)
  
    local lifeGaugeBackground = CCSprite:createWithSpriteFrameName("cyber_gauge_bg.png")
    lifeGaugeBackground:setAnchorPoint(ccp(0.0, 0.5))
    lifeGaugeBackground:setPosition(ccp(35, 307))
    self:addChild(lifeGaugeBackground, 0, LifeGaugeBackgroundTag)
  
    local lifeGauge = CCSprite:createWithSpriteFrameName("cyber_gauge.png")
    lifeGauge:setAnchorPoint(ccp(0.0, 0.5))
    lifeGauge:setPosition(ccp(35, 307))
    self:addChild(lifeGauge, 0, LifeGaugeTag)
  end
}

return Skin