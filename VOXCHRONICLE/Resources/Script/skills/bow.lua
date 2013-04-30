Skill = {
  name = "スナイプ",
  identifier = "bow",
  effectFrames = 0, -- エフェクトはスクリプトで出す
  mp = 0,
  se = true,
  tensionLevel = 0,
  common = false,
  canRepeat = true,
  cutinType = EffectLayerCutinTypeNormal,
  loop = true,
  maxRepeat = 1,
  keepTension = false,
  turn = 1,
  performSkill = function(self, target, characterManager, enemyManager)
    -- エフェクトを縦に伸ばしまくる
    local layer = EffectLayer:sharedLayer()
    local effect = layer:addEffectOnEnemy(target, "bow", 4, CCRectMake(0, 0, 50, 50))
    effect:setAnchorPoint(ccp(0.5, 0))
    effect:setScaleY(3)
  end,
  getPower = function(characterManager)
    local tension = characterManager:getTension()
    t = {5, 11, 17, 23, 30}
    return t[tension + 1]
  end,
  skillRange = SkillRangeBack,
  skillType = SkillTypeMagical,
  getMessageTable = function()
    return{
      "{chara}は　ゆみを　はなった",
      "てんくうから　ひかりが　ほどばしる",
      "まりょくで　ゆみを　つくりだす",
      "もっとも　たいりょくあるものを　ねらう！",
      "きょだいな　やじりを　しょうかんした",
      "うちつらぬけ！！　スナイプ！！"
    }
  end
}
