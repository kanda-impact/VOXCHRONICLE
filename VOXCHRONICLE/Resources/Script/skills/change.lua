Skill = {
  name = "チェンジ",
  identifier = "change",
  effectFrames = 0,
  mp = 0,
  se = true,
  tensionLevel = 0,
  common = false,
  cutinType = EffectLayerCutinTypeNormal,
  maxRepeat = 1,
  turn = 1,
  loop = true,
  performSkill = function(self, target, characterManager, enemyManager)
    characterManager:changeCharacter()
  end,
  getPower = function(characterManager)
    return 0
  end,
  skillRange = SkillRangeSelf,
  skillType = SkillTypeNone,
  messages = {
    "ｼｬﾊﾞﾃﾞｭﾋﾞﾀｯﾁｺｳﾀｰｲ!"
  }
}
