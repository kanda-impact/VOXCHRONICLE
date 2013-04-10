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
  skillRange = SkillRangeAll,
  skillType = SkillTypeMagical,
  getPower = function(characterManager)
    local tension = characterManager:getTension()
    t = {0, 6, 9, 12, 15}
    return t[tension + 1]
  end,
  messages = {
    "{chara}は　まほうを　となえた",
    "{chara}から　はげしいほのうが　ほどばしる",
    "{chara}ブリザーーード！！",
    "{chara}は　てきぜんたいに　しょうげきを　はなった",
    "{chara}は　きょうりょくな　まほうを　つかった",
    "{chara}の　サンダーボルト　こうげき",
    "{chara}の　まわりから　きょうりょくな　ひばなが！",
    "てきぜんたいに　りゅうせいが　ふりそそいぐ",
    "{chara}　「フレイムバーン・ファイヤー！」"
  }
}
