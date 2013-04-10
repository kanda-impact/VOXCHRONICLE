math.randomseed(os.time())
Enemy = {
  name = "右ビット",
  imageName = "bit",
  attack = 100,
  baseExp = 1,
  hasFrame = true,
  counter = 0,
  getSpeed = function(enemy, characterManager)
    return 0
  end,
  getFrequency = function(enemy, characterManager)
    return 1
  end,
  disableSkills = {"knockback"},
  description = [[
  右側のビット。その正体は真の究極生命体＜＞コアだった、ということはなく、ただの中間管理職。いつかラスボスになれる日を夢見て職務を全うしている
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self, characterManager, enemyManager)
    math.random(100)
    local reviveTurn = self:getRegister("reviveTurn", 0)
    if reviveTurn > 0 then
      return "revive"
    end
    local r = math.random(100)
    if enemyManager:getEnemies():count() < 3 and r < 10 then -- 誰か死んでるかつ25%
      local leftBitDead = true
      for i=0, enemyManager:getEnemies():count() - 1 do
        local enemy = enemyManager:getEnemies():objectAtIndex(i)
        if enemy:getIdentifier() == "L_bit_boss" then
          leftBitDead = false
          break
        end
      end
      if leftBitDead then
        return "revive" -- 蘇生呪文
      end
    end
    if r < 5 then
      return "beam"
    end
    return ""
  end
}

return Enemy