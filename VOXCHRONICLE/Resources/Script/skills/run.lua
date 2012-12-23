Skill = {
  name = "走る",
  identifier = "run",
  power = 0,
  mp = 0,
  tensionLevel = 0,
  common = true,
  maxRepeat = 2,
  turn = 1,
  performSkill = function(self, target, characterManager, enemyManager)
    enemyManager:nextTurn()
  end,
  skillRange = SkillRangeSelf,
  skillType = SkillTypePhysical
}
