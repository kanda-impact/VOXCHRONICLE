Skill = {
  name = "回復",
  identifier = "cure",
  power = 0,
  mp = 1,
  tensionLevel = 0,
  common = false,
  maxRepeat = 1,
  se = true,
  turn = 1,
  performSkill = function(target, characterManager)
    characterManager:addHP(1)
  end,
  skillRange = SkillRangeSelf,
  skillType = SkillTypeNone
}
