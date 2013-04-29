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
  messages = {
    "{chara}は　ぜんたいまほうを　となえた",
    "{chara}から　はげしいいかずちが　ほどばしる",
    "{chara}サンダーーーーーーー！！！！",
    "てきぜんたいに　きょうりょくな　でんげきが！",
    "{chara}は　きょうりょくな　まほうを　つかった",
    "{chara}の　サンダーボルト　こうげき",
    "{chara}の　らいげきが　てきをつらぬく！",
    "てきぜんたいに　らいげきが　ふりそそぐ",
    "くらえぇー！ラスカサンダーー！！"
  },
  getMessageTable = function(map, characterManager, enemyManager)
    return {}
  end
}
