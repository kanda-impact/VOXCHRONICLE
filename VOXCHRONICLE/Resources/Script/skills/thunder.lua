Skill = {
  name = "雷",
  identifier = "thunder",
  power = 1,
  mp = 2,
  se = true,
  tensionLevel = 1,
  common = false,
  maxRepeat = 1,
  turn = 1,
  skillRange = SkillRangeAll,
  skillType = SkillTypeMagical,
  getTensionRate = function(tension)
    t = {0, 1.0, 1.5, 2.1, 3}
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
