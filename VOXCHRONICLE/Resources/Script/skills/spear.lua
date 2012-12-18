Skill = {
  name = "突き",
  identifier = "spear",
  power = 1,
  mp = 0,
  tensionLevel = 2,
  common = false,
  maxRepeat = 1,
  turn = 1,
  skillRange = SkillRangeVertical,
  skillType = SkillTypePhysical,
  getTensionRate = function(tension)
    t = {0, 0, 1.0, 2.1, 3.5}
    return t[tension]
  end
}
