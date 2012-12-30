Skill = {
  name = "溜める",
  identifier = "tension",
  power = 0,
  mp = 0,
  se = true,
  tensionLevel = 0,
  common = true,
  maxRepeat = 4,
  turn = 1,
  performSkill = function(self, target, characterManager, enemyManager)
    characterManager:addTension(1)
  end,
  skillRange = SkillRangeSelf,
  skillType = SkillTypeNone
}
