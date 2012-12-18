Skill = {
  name = "魔法",
  identifier = "magic",
  power = 1,
  mp = 1,
  tensionLevel = 0,
  common = false,
  maxRepeat = 4,
  turn = 1,
  skillRange = SkillRangeSingle,
  skillType = SkillTypeMagical,
  getTensionRate = function(tension)
    t = {0, 0, 1.0, 1.5, 3}
    return t[tension]
  end
}
