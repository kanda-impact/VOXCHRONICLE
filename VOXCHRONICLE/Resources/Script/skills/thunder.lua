Skill = {
  name = "雷",
  identifier = "thunder",
  power = 1,
  mp = 2,
  tensionLevel = 2,
  common = false,
  maxRepeat = 1,
  turn = 1,
  skillRange = SkillRangeAll,
  skillType = SkillTypeMagical,
  getTensionRate = function(tension)
    t = {0, 0, 1.0, 1.5, 3}
    return t[tension + 1]
  end
}
