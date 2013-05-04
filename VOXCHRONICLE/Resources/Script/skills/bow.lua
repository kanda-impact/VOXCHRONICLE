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
  getMessageTable = function(self, targets, map, characterManager, enemyManager)
    if targets:count() > 0 then
      local target = targets:objectAtIndex(0)
      tolua.cast(target, "Enemy")
      if target:getSpecies():getIdentifier() == "wave" then --波用メッセージ
      return{}
      elseif target:getType() == SkillTypeMagical or target:getItem() == EnemyItemBarrier or not target:getSpecies():isEnableSkill(self) then -- 効かない相手にはメッセージ表示しない
        return {}
      end
    end
    return{
      "ラスカは　ゆみを　はなった",
      "てんくうから　ひかりが　ほどばしる",
      "まりょくで　ゆみを　つくりだす",
      "もっとも　たいりょくあるものを　ねらう！",
      "きょだいな　やじりを　しょうかんした",
      "うちつらぬけ！！　スナイプ！！",
      "シュパーーン！！",
      "いけー！　つらぬけ！",
      "えんきょり　こうげきだ！"
    }
  end
}
