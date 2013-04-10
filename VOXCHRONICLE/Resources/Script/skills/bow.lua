Skill = {
  name = "スナイプ",
  identifier = "bow",
  effectFrames = 4,
  mp = 0,
  se = true,
  tensionLevel = 0,
  common = false,
  canRepeat = true,
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
