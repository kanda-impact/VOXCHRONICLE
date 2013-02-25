Skill = {
  name = "盾",
  identifier = "shield",
  effectFrames = 0,
  mp = 0,
  tensionLevel = 0,
  common = true,
  se = true,
  maxRepeat = 1,
  turn = 1,
  loop = true,
  performSkill = function(self, target, characterManager, enemyManager)
    characterManager:setShield(true)
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
