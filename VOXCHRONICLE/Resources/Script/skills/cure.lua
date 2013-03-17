Skill = {
  name = "回復",
  identifier = "cure",
  mp = 1,
  tensionLevel = 0,
  effectFrames = 7,
  common = false,
  cutinType = EffectLayerCutinTypeNormal,
  maxRepeat = 1,
  se = true,
  turn = 1,
  loop = true,
  performSkill = function(self, target, characterManager, enemyManager)
    local tension = characterManager:getTension() -- テンションをとって
    local power = self:getPower(characterManager) -- パワーとって
    local rate = power / 10.0 -- 割合出して
    local max = characterManager:getMaxHP() -- 最大値出して
    local cure = math.ceil(max * rate)
    characterManager:addHP(cure) -- 回復させる
  end,
  getPower = function(characterManager)
    local tension = characterManager:getTension()
    t = {2, 3, 4, 5, 6}
    return t[tension + 1]
  end,
  skillRange = SkillRangeSelf,
  skillType = SkillTypeNone,
  messages = {
    ""
  }
}
