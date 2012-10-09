Skill = {
  name = "回復",
  slug = "cure",
  power = 0,
  mp = 1,
  common = false,
  maxRepeat = 1,
  turn = 1,
  performSkill = function(target, characterManager)
    characterManager:setShield(true);
  end,
  skillRange = SkillRangeSelf,
  skillType = SkillTypeNone
}
