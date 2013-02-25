Skill = {
  name = "弓",
  identifier = "bow",
  effectFrames = 0,
  mp = 1,
  se = true,
  tensionLevel = 0,
  common = false,
  loop = true,
  maxRepeat = 1,
  turn = 1,
  getPower = function(characterManager)
    t = {3, 5, 7, 9, 12}
    return t[tension + 1]
  end,
  skillRange = SkillRangeBack,
  skillType = SkillTypeNone,
  messages = {
    "{chara}は　ゆみを　はなった"
  }
}
