Skill = {
  name = "スラッシュ",
  identifier = "slash",
  power = 1,
  mp = 0,
  se = true,
  tensionLevel = 2,
  common = false,
  maxRepeat = 1,
  turn = 1,
  skillRange = SkillRangeFront,
  skillType = SkillTypePhysical,
  getTensionRate = function(tension)
    t = {0, 0, 1.0, 2.1, 3.5}
    return t[tension + 1]
  end
}
