Skill = {
  name = "魔法",
  identifier = "magic",
  effectFrames = 6,
  mp = 0,
  se = true,
  tensionLevel = 0,
  common = false,
  cutinType = EffectLayerCutinTypeNormal,
  maxRepeat = 4,
  turn = 1,
  loop = true,
  getPower = function(characterManager)
    local repeatCount = characterManager:getRepeatCount()
    if repeatCount == 0 then
    repeatCount =4
    end
    repeatPower = {0,1,2,3}
    local tension = characterManager:getTension()
    t = {3, 9, 14, 18, 24}
    return t[tension + 1] + repeatPower[repeatCount]
  end,
  skillRange = SkillRangeSingle,
  skillType = SkillTypeMagical,
  messages = {
  }
}
