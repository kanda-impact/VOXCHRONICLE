Skill = {
  name = "魔法",
  slug = "magic",
  power = 1,
  mp = 1,
  tensionLevel = 0,
  common = false,
  maxRepeat = 4,
  turn = 1,
  skillRange = SkillRangeSingle,
  skillType = SkillTypeMagical,
  getTensionRate = function(tension)
    t = {1.0, 1.5, 3.0, 4.5, 6}
    return t[tension + 1]
  end
}
