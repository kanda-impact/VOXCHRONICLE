Skill = {
  name = "魔法",
  identifier = "magic",
  mp = 0,
  se = true,
  tensionLevel = 0,
  common = false,
  maxRepeat = 4,
  turn = 1,
  getPower = function(tension)
    t = {1, 3, 5, 7, 9}
    return t[tension + 1]
  end,
  skillRange = SkillRangeSingle,
  skillType = SkillTypeMagical,
  messages = {
  }
}
