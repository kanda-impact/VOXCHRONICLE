Skill = {
  name = "魔法",
  identifier = "magic",
  effectFrames = 8,
  mp = 0,
  se = true,
  tensionLevel = 0,
  common = false,
  maxRepeat = 4,
  turn = 1,
  loop = true,
  getPower = function(tension)
    t = {3, 6, 9, 12, 15}
    return t[tension + 1]
  end,
  skillRange = SkillRangeSingle,
  skillType = SkillTypeMagical,
  messages = {
  }
}
