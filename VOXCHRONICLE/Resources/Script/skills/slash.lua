Skill = {
  name = "スラッシュ",
  identifier = "slash",
  mp = 0,
  se = true,
  tensionLevel = 1,
  common = false,
  maxRepeat = 1,
  turn = 1,
  skillRange = SkillRangeFront,
  skillType = SkillTypePhysical,
  getPower = function(tension)
    t = {0, 1, 3, 5, 8}
    return t[tension + 1]
  end,
  messages = {
    ""
  }
}
