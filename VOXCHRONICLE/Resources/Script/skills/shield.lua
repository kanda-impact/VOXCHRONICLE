Skill = {
  name = "盾",
  identifier = "shield",
  power = 0,
  mp = 0,
  tensionLevel = 0,
  common = true,
  maxRepeat = 1,
  turn = 1,
  performSkill = function(target, characterManager)
    characterManager:setShield(true);
  end,
  skillRange = SkillRangeSelf,
  skillType = SkillTypeNone
}
