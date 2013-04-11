math.randomseed(os.time())
Enemy = {
  name = "左ビット",
  imageName = "bit",
  attack = 15,
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
  左側のビット。すぐに倒されてしまうが右ビットの蘇生呪文で不死鳥の如く蘇る
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self, characterManager, enemyManager)
    math.random(100)
    local row = self:getRow()
    local col = self:getCol()
    if row == 1 and col == 2 then
      self:setRow(0)
      self:setCol(1)
    elseif row == 0 and col == 1 then
      self:setRow(1)
      self:setCol(0)
    elseif row == 1 and col == 0 then
      self:setRow(2)
      self:setCol(1)
    elseif row == 2 and col == 1 then
      self:setRow(1)
      self:setCol(2)
    end
    local r = math.random(100)
    if r < 65 then
      return "beam"
    end
    return ""
  end
}

return Enemy