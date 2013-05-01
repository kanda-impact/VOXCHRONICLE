require("variable_expansion")
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
  keepTension = true,
  performSkill = function(self, target, characterManager, enemyManager)
    enemyManager:nextTurn(characterManager, true, true)
  end,
  getPower = function(characterManager)
    return 0
  end,
  skillRange = SkillRangeSelf,
  skillType = SkillTypePhysical,
  getMessageTable = function(self, targets, map, characterManager, enemyManager)
    chara = characterManager:getCurrentCharacter():getName()
    return {
      _("#{chara}は　てきとの　きょりを　つめた"),
      _("#{chara}は　はしりだした!　......あしたへ！"),
      _("#{chara}は　さきを　いそいだ"),
      _("せっかちな　#{chara}　いそぐ　いそぐ"),
      "あんまり　はしると　けがするよ？",
      "いそいでも　りえきはないのだ",
      "いそぎすぎは　ちゅういだ",
      "スプリント！！",
      "てきは　まだか　はやくこい",
      "やすんでも　まりょくは　かいふくしません",
      "こないなら　こっちから　いくぜ！",
      _("かぜをきって　はしる　#{chara}"),
      _("#{chara}は　てきに　せっきんした"),
      _("#{chara}は　うってでることにした")
    }
  end
}
