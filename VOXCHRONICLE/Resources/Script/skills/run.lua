Skill = {
  name = "走る",
  identifier = "run",
  power = 0,
  mp = 0,
  se = true,
  tensionLevel = 0,
  common = true,
  maxRepeat = 1,
  turn = 1,
  performSkill = function(self, target, characterManager, enemyManager)
    enemyManager:nextTurn(characterManager)
  end,
  skillRange = SkillRangeSelf,
  skillType = SkillTypePhysical
}
