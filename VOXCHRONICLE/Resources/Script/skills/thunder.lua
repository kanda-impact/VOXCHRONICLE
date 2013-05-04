require("variable_expansion")
Skill = {
  name = "ラスカサンダー",
  identifier = "thunder",
  effectFrames = 6,
  mp = 2,
  se = true,
  tensionLevel = 1,
  common = false,
  cutinType = EffectLayerCutinTypeNormal,
  maxRepeat = 1,
  turn = 1,
  loop = true,
  canRepeat = true,
  keepTension = false,
  skillRange = SkillRangeAll,
  skillType = SkillTypeMagical,
  getPower = function(characterManager)
    local tension = characterManager:getTension()
    t = {0, 6, 10, 14, 18}
    return t[tension + 1]
  end,
  getMessageTable = function(self, targets, map, characterManager, enemyManager)
    chara = characterManager:getCurrentCharacter():getName()
    return {
      _("#{chara}は　ぜんたいまほうを　となえた"),
      _("#{chara}から　はげしいいかずちが　ほどばしる"),
      _("#{chara}サンダーーーーーーー！！！！"),
      "てきぜんたいに　きょうりょくな　でんげきが！",
      _("#{chara}は　きょうりょくな　まほうを　つかった"),
      _("#{chara}の　サンダーボルト　こうげき"),
      _("#{chara}の　らいげきが　てきをつらぬく！"),
      "てきぜんたいに　らいげきが　ふりそそぐ",
      "くらえぇー！ラスカサンダーー！！"
    }
  end
}
