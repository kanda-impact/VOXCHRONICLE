Skill = {
  name = "溜める",
  slug = "tension",
  power = 0,
  mp = 0,
  tensionLevel = 0,
  common = true,
  maxRepeat = 4,
  turn = 1,
  performSkill = function(target, characterManager)
    characterManager:addTension(1)
  end,
  skillRange = SkillRangeSelf,
  skillType = SkillTypeNone
}
