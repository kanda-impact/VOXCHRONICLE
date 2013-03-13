Skill = {
  name = "弓",
  identifier = "bow",
  effectFrames = 4,
  mp = 1,
  se = true,
  tensionLevel = 0,
  common = false,
  cutinType = EffectLayerCutinTypeNormal,
  loop = true,
  maxRepeat = 1,
  turn = 1,
  getPower = function(characterManager)
    local tension = characterManager:getTension()
    t = {6, 12, 18, 24, 30}
    return t[tension + 1]
  end,
  skillRange = SkillRangeBack,
  skillType = SkillTypeMagical,
  messages = {
    "{chara}は　ゆみを　はなった"
  }
}
