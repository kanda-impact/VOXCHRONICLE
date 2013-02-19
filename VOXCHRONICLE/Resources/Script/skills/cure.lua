Skill = {
  name = "回復",
  identifier = "cure",
  mp = 1,
  tensionLevel = 0,
  effectFrames = 7,
  common = false,
  maxRepeat = 1,
  se = true,
  turn = 1,
  loop = true,
  performSkill = function(self, target, characterManager, enemyManager)
    local tension = characterManager:getTension() -- テンションをとって
    local power = self:getPowerWithTension(tension) -- パワーとって
    local rate = power / 10.0 -- 割合出して
    local max = characterManager:getMaxHP() -- 最大値出して
    local cure = math.ceil(max * rate)
    characterManager:addHP(cure) -- 回復させる
  end,
  getPower = function(tension)
    t = {1, 3, 5, 8, 10}
    return t[tension + 1]
  end,
  skillRange = SkillRangeSelf,
  skillType = SkillTypeNone,
  messages = {
    ""
  }
}
