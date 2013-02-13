Skill = {
  name = "攻撃",
  identifier = "attack",
  effectFrames = 6,
  mp = 0,
  se = true,
  tensionLevel = 0,
  common = false,
  maxRepeat = 4,
  turn = 1,
  skillRange = SkillRangeSingle,
  skillType = SkillTypePhysical,
  getPower = function(tension)
    t = {1, 3, 5, 7, 10}
    return t[tension + 1]
  end,
  messages = {
    ""
  }
}
