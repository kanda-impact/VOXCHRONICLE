Skill = {
  name = "シールド",
  identifier = "shield",
  effectFrames = 0,
  mp = 0,
  tensionLevel = 0,
  common = true,
  cutinType = EffectLayerCutinTypeHold,
  se = true,
  maxRepeat = 1,
  turn = 1,
  loop = true,
  canRepeat = false,
  keepTension = false,
  performSkill = function(self, target, characterManager, enemyManager)
    characterManager:setShield(true)
  end,
  getPower = function(characterManager)
    return 0
  end,
  skillRange = SkillRangeSelf,
  skillType = SkillTypeNone,
  messages = {
    "{chara}は　たてをかまえた",
    "{chara}は　シールドを　てんかいした",
    "オクスが　たてをかまえ　まえにでた",
    "ラスカが　まほうのかべを　てんかいした"
  }
}
