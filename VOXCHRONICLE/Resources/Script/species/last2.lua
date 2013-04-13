math.randomseed(os.time())
Enemy = {
  name = "ラスボス最終形態",
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
  残念、倒したと思った？突然出てきてプレイヤーを絶望の淵に陥れるのを生き甲斐とする生命体
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self, characterManager, enemyManager)
    math.random(100)
    local r = math.random(100)
    local tensionTurn = self:getRegister("tensionWave", 0)
    --local swordTurn = self:getRegister("", 0)
    if tensionTurn > 0 or r < characterManager:getTension() * 10 then
      return "reset_tension"
    elseif self:getItem() == EnemyItemNone and r < 15 then
      return "equip"
    end
    return ""
  end
}

return Enemy