Skill = {
  name = "弓",
  identifier = "bow",
  effectFrames = 4,
  mp = 1,
  se = true,
  tensionLevel = 0,
  common = false,
  loop = true,
  maxRepeat = 1,
  turn = 1,
  getPower = function(characterManager)
    local tension = characterManager:getTension()
    t = {6, 7, 9, 12, 16}
    return t[tension + 1]
  end,
  skillRange = SkillRangeBack,
  skillType = SkillTypeNone,
  messages = {
    "{chara}は　ゆみを　はなった"
  }
}
