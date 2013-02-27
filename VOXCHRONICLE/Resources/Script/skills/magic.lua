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
  getPower = function(characterManager)
    local tension = characterManager:getTension()
    t = {3, 6, 10, 14, 18}
    return t[tension + 1]
  end,
  skillRange = SkillRangeSingle,
  skillType = SkillTypeMagical,
  messages = {
  }
}
