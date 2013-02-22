Skin = {
  name = "SkinB",
  prefix = "grass",
  hasBackground = true,
  groundFrameCount = 5,
  frameType = ControllerFrameTypeCommon,
  buildSkin = function(self)
    -- ここでスキンの定義をｇｄｇｄ書きます
    local hpLabel = CCSprite:create("grass_hp.png")
    hpLabel:setPosition(ccp(21, 301));
    self:addChild(hpLabel)
    
    local mpLabel = CCSprite:create("grass_mp.png");
    mpLabel:setPosition(ccp(283, 301))
    self:addChild(mpLabel)
  
    local currentHPLabel = CCLabelAtlas:create("0", "grass_hp_numbers.png", 20, 25, string.byte("0"))
    currentHPLabel:setScale(0.6)
    currentHPLabel:setPosition(ccp(54, 291))
    currentHPLabel:setAnchorPoint(ccp(0.5, 0.5))
  
    local maxHPLabel = CCLabelAtlas:create("0", "grass_hp_numbers.png", 20, 25, string.byte("0"))
    maxHPLabel:setScale(0.4)
    maxHPLabel:setPosition(ccp(94, 287))
    maxHPLabel:setAnchorPoint(ccp(0.5, 0.5))
    self:addChild(currentHPLabel, 0, CurrentHPLabelTag)
    self:addChild(maxHPLabel, 0, MaxHPLabelTag)
    
    -- MPMarker
    local mpMarker = CCNode:create()
    mpMarker:setPosition(ccp(305, 308))
    self:addChild(mpMarker, 0, MPMarkerTag)
  
    local slash = CCSprite:create("grass_slash.png")
    slash:setPosition(ccp(77, 290))
    self:addChild(slash)
  
    local stageLabel = CCSprite:create("grass_level.png")
    stageLabel:setPosition(ccp(240, 275))
    stageLabel:setAnchorPoint(ccp(0.5, 0))
    self:addChild(stageLabel)
  
    local levelLabel = CCLabelAtlas:create("10", "grass_level_numbers.png", 26, 33, string.byte("0"))
    levelLabel:setPosition(ccp(240, 285))
    levelLabel:setAnchorPoint(ccp(0.5, 0))
    self:addChild(levelLabel, 0, LevelLabelTag)
  
    local lifeGaugeBackground = CCSprite:create("grass_gauge_bg.png")
    lifeGaugeBackground:setAnchorPoint(ccp(0.0, 0.5))
    lifeGaugeBackground:setPosition(ccp(37, 307))
    self:addChild(lifeGaugeBackground, 0, LifeGaugeBackgroundTag)

    local lifeGauge = CCSprite:create("grass_gauge.png")
    lifeGauge:setAnchorPoint(ccp(0.0, 0.5))
    lifeGauge:setPosition(ccp(37, 307))
    self:addChild(lifeGauge, 0, LifeGaugeTag)
    
  end
}

return Skin