Skill = {
  name = "溜める",
  identifier = "tension",
  effectFrames = 0,
  mp = 0,
  se = true,
  tensionLevel = 0,
  common = true,
  cutinType = EffectLayerCutinTypeNormal,
  maxRepeat = 4,
  turn = 1,
  loop = false,
  performSkill = function(self, target, characterManager, enemyManager)
    characterManager:addTension(1)
  end,
  getPower = function(characterManager)
    return 0
  end,
  skillRange = SkillRangeSelf,
  skillType = SkillTypeNone,
  messages = {
    ""
  }
}
