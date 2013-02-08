Skill = {
  name = "回復",
  identifier = "cure",
  mp = 1,
  tensionLevel = 0,
  common = false,
  maxRepeat = 1,
  se = true,
  turn = 1,
  performSkill = function(self, target, characterManager, enemyManager)
    characterManager:addHP(1)
  end,
  getPower = function(tension)
    t = {1, 3, 5, 8, 10}
    return t[tension + 1]
  end,
  skillRange = SkillRangeSelf,
  skillType = SkillTypeNone,
  messages = {
    ""
  }
}
