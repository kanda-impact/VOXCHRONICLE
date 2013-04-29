Skill = {
  name = "ダッシュ",
  identifier = "run",
  effectFrames = 3,
  mp = 0,
  se = true,
  tensionLevel = 0,
  common = true,
  cutinType = EffectLayerCutinTypeNormal,
  maxRepeat = 2,
  turn = 1,
  loop = true,
  canRepeat = true,
  performSkill = function(self, target, characterManager, enemyManager)
    enemyManager:nextTurn(characterManager, true, true)
  end,
  getPower = function(characterManager)
    return 0
  end,
  skillRange = SkillRangeSelf,
  skillType = SkillTypePhysical,
  messages = {
    "{chara}は　てきとの　きょりを　つめた",
    "{chara}は　はしりだした!　......あしたへ！",
    "{chara}は　さきを　いそいだ",
    "せっかちな　{chara}　いそぐ　いそぐ",
    "あんまり　はしると　けがするよ？",
    "いそいでも　りえきはないのだ",
    "いそぎすぎは　ちゅういだ",
    "スプリント！！",
    "てきは　まだか　はやくこい",
    "やすんでも　まりょくは　かいふくしません",
    "こないなら　こっちから　いくぜ！",
    "かぜをきって　はしる　{chara}",
    "{chara}は　てきに　せっきんした",
    "{chara}は　うってでることにした"
  }
}
