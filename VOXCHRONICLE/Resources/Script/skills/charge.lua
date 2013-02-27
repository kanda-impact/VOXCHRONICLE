Skill = {
  name = "チャージ",
  identifier = "charge",
  mp = 0,
  tensionLevel = 0,
  effectFrames = 0,
  common = false,
  maxRepeat = 1,
  se = true,
  turn = 1,
  loop = true,
  performSkill = function(self, target, characterManager, enemyManager)
    local tension = characterManager:getTension() -- テンションをとって
    local power = self:getPower(characterManager) -- パワーとって
    local rate = power / 10.0 -- 割合出して
    local max = characterManager:getMaxMP() -- 最大値出して
    local cure = math.ceil(max * rate)
    characterManager:addMP(cure) -- 回復させる
  end,
  getPower = function(characterManager)
    local tension = characterManager:getTension()
    t = {1, 2, 4, 6, 8}
    return t[tension + 1]
  end,
  skillRange = SkillRangeSelf,
  skillType = SkillTypeNone,
  messages = {
    ""
  }
}
