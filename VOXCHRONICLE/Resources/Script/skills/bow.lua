Skill = {
  name = "弓",
  identifier = "bow",
  mp = 1,
  se = true,
  tensionLevel = 0,
  common = false,
  maxRepeat = 1,
  turn = 1,
  getPower = function(tension)
    t = {1, 2, 4, 6, 8}
    return t[tension + 1]
  end,
  skillRange = SkillRangeBack,
  skillType = SkillTypeNone,
  messages = {
    "{chara}は　ゆみを　はなった"
  }
}
