math.randomseed(os.time())
Enemy = {
  name = "ワート・モショウ",
  imageName = "2last",
  attack = 20,
  baseExp = 1,
  hasFrame = true,
  counter = 0,
  width = 256,
  height = 170.75,
  getSpeed = function(enemy, characterManager)
    return 0
  end,
  getFrequency = function(enemy, characterManager)
    return 1
  end,
  disableSkills = {"knockback"},
  description = [[
この世界のあらゆる音やリズムをねじまげて、自分の音と同化させてしまう力を持つまでになったこの世界で最悪の魔物。
生息地：宙域　攻撃力：つよい　移動：しない
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self, characterManager, enemyManager)
    math.random(100)
    local r = math.random(100)
    local tensionTurn = self:getRegister("tensionWave", 0)
    local regist = self:getRegister("skill_last", 0)
    if regist ==1 then
      return "thunder_last"
    elseif tensionTurn > 0 or r < characterManager:getTension() * 10 then
      return "reset_tension"
    elseif self:getItem() == EnemyItemNone and r < 15 then
      return "equip"
    elseif r < 20 then
      return "thunder_last"
    end
    return ""
  end
}

return Enemy