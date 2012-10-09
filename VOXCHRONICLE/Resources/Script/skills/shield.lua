Skill = {
  name = "盾",
  slug = "shield",
  power = 0,
  mp = 0,
  common = false,
  maxRepeat = 1,
  turn = 1,
  performSkill = function(target, characterManager)
    characterManager:setShield(true);
  end,
  skillRange = SkillRangeSelf,
  skillType = SkillTypeNone
}
