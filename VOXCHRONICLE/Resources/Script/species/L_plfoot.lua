Enemy = {
  name = "左アシィ",
  imageName = "L_plfoot",
  attack = 1,
  baseExp = 6,
  hasFrame = true,
  counter = 1,
  getSpeed = function(enemy, characterManager)
    return 0
  end,
  getFrequency = function(enemy, characterManager)
    return 1
  end,
  disableSkills = {"knockback"},
  description = [[
    文章は開発中の物です。
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
    local key = "footTurn"
    local turn = self:getRegister(key, 0) -- 溜めているターンを取得
    math.random(100)
    local rand = math.random(100)
    if turn > 0 or rand <= 5 then -- 溜めてる最中、または5%の確率で
      return "foot"
    end
    return ""
  end
}

return Enemy