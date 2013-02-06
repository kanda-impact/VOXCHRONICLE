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
    "%sは　てきとの　きょりを　つめた",
    "%sは　はしりだした!　......あしたへ！",
    "%sは　さきを　いそいだ",
    "せっかちな　%s　いそぐ　いそぐ",
    "あんまり　はしると　けがするよ？",
    "いそいでも　りえきはない",
    "%s　はしる　しかし　いそぎすぎは　ちゅういだ",
    "てきは　まだか　はやくこい",
    "やすむと　まりょくが　かいふくします",
    "はしるくらいなら　やすもうぜ",
    "こないなら　こっちから　いくぜ！",
    "はしるー　はしるー　おれーたーちー",
    "かぜをきって　はしる　%s",
    "%sは　てきに　せっきんした",
    "%sは　うってでることにした"
  }
}
