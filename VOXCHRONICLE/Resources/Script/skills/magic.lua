Skill = {
  name = "魔法",
  identifier = "magic",
  effectFrames = 6,
  mp = 0,
  se = true,
  tensionLevel = 0,
  common = false,
  maxRepeat = 4,
  turn = 1,
  loop = true,
  getPower = function(characterManager)
    local tension = characterManager:getTension()
    t = {3, 9, 14, 18, 24}
    return t[tension + 1]
  end,
  skillRange = SkillRangeSingle,
  skillType = SkillTypeMagical,
  messages = {
  }
}
