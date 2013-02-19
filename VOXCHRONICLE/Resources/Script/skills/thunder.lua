Skill = {
  name = "雷",
  identifier = "thunder",
  effectFrames = 6,
  mp = 2,
  se = true,
  tensionLevel = 1,
  common = false,
  maxRepeat = 1,
  turn = 1,
  loop = true,
  skillRange = SkillRangeAll,
  skillType = SkillTypeMagical,
  getPower = function(tension)
    t = {0, 3, 7, 11, 15}
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
