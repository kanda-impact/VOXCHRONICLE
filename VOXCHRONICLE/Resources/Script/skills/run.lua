Skill = {
  name = "走る",
  identifier = "run",
  power = 0,
  mp = 0,
  se = true,
  tensionLevel = 0,
  common = true,
  maxRepeat = 2,
  turn = 1,
  performSkill = function(self, target, characterManager, enemyManager)
    enemyManager:nextTurn(characterManager)
  end,
  skillRange = SkillRangeSelf,
  skillType = SkillTypePhysical,
  messages = {
    "{chara}は　てきとの　きょりを　つめた",
    "{chara}は　はしりだした!　......あしたへ！",
    "{chara}は　さきを　いそいだ",
    "せっかちな　{chara}　いそぐ　いそぐ",
    "あんまり　はしると　けがするよ？",
    "いそいでも　りえきはない",
    "{chara}　はしる　しかし　いそぎすぎは　ちゅういだ",
    "てきは　まだか　はやくこい",
    "やすむと　まりょくが　かいふくします",
    "はしるくらいなら　やすもうぜ",
    "こないなら　こっちから　いくぜ！",
    "はしるー　はしるー　おれーたーちー",
    "かぜをきって　はしる　{chara}",
    "{chara}は　てきに　せっきんした",
    "{chara}は　うってでることにした"
  }
}
