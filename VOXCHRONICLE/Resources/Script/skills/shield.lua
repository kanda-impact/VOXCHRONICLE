require("variable_expansion")
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
  getMessageTable = function(self, targets, map, characterManager, enemyManager)
    chara = characterManager:getCurrentCharacter():getName()
    return {
      _("#{chara}は　たてをかまえた"),
      _("#{chara}は　シールドを　てんかいした"),
      "オクスが　たてをかまえ　まえにでた",
      "ラスカが　まほうのかべを　てんかいした",
      "そうびは　もっているだけじゃ　いみがないぞ"
      "シールド　てんかい！"
      "いそいで　たてに　かくれた！"
    }
  end
}
