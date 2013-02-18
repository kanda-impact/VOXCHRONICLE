Skill = {
  name = "スラッシュ",
  identifier = "slash",
  effectFrames = 6,
  mp = 0,
  se = true,
  tensionLevel = 1,
  common = false,
  maxRepeat = 1,
  turn = 1,
  skillRange = SkillRangeFront,
  skillType = SkillTypePhysical,
  getPower = function(tension)
    t = {0, 6, 12, 18, 24}
    return t[tension + 1]
  end,
  messages = {
    ""
  }
}
