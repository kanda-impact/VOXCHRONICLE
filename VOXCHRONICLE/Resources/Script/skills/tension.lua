Skill = {
  name = "パワーチャージ",
  identifier = "tension",
  effectFrames = 0,
  mp = 0,
  se = true,
  tensionLevel = 0,
  common = true,
  cutinType = EffectLayerCutinTypeNormal,
  maxRepeat = 4,
  turn = 1,
  loop = false,
  canRepeat = true,
  keepTension = true,
  performSkill = function(self, target, characterManager, enemyManager)
    characterManager:addTension(1)
    local tension = characterManager:getTension()
    local layer = EffectLayer:sharedLayer()
    local node = CCNode:create()
    local tensionLabel = CCLabelAtlas:create(tension.."", "tension_number.png", 65, 97.5, string.byte("0"))
    local cross = CCSprite:create("tension_cross.png")
    cross:setAnchorPoint(ccp(0.5, 0.5))
    tensionLabel:setAnchorPoint(ccp(0.5, 0.5))
    cross:setPosition(ccp(0, 15))
    node:setPosition(ccp(105, 40))
    node:addChild(tensionLabel)
    tensionLabel:setPosition(ccp(80, 10))
    node:addChild(cross)
    layer:setCutinExtension(node)
  end,
  getPower = function(characterManager)
    return 0
  end,
  skillRange = SkillRangeSelf,
  skillType = SkillTypeNone,
  --テンションを溜める
--[[  messages = {
    "{chara}は　ちからをためた",
    "{chara}の　テンションがあがっていく",
    "{chara}は　りきんでいる",
    "{chara}の　ボルテージが　ふくれあがる",
    "もえあがる　こころ"
    "せいめいりょくが　たかまる！",
    "たかまれ　われらの　BEAT!!",
    "パワー　ちゃーーじ！！！",
    "ちからが　みなぎっていく！！"
  },]]
  getMessageTable = function(map, characterManager, enemyManager)
    return {}
  end,
  --テンションマックス時
--[[  messages = {
    "さいだいパワーだ！！",
    "ＭＡＸ！ハイテンション！！",
    "ぜんりょくぜんかいっ！！",
    "ボルテージ　さいだい！",
    "もえつきるほど　ヒート　ッ！",
    "さいきょうの　パワー　みせてやる",
    "BEATはさいこうちょうだ",
    "うぉぉおおお！",
    "マキシマム　パワー！！",
    "POWER MAXIMAM!!"
  }]]
}
