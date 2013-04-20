Enemy = {
  name = "右カギーＶ（ヴイ）",
  imageName = "R_strclaw",
  attack = 4,
  baseExp = 6,
  hasFrame = true,
  counter = 2,
  getSpeed = function(enemy, characterManager)
    return 0
  end,
  getFrequency = function(enemy, characterManager)
    return 1
  end,
  disableSkills = {"knockback"},
  description = [[
（このかたきは…おれが討つ！）
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
    local key = "footTurn"
    local turn = self:getRegister(key, 0) -- 溜めているターンを取得
    math.random(100)
    local rand = math.random(100)
    if turn > 0 or rand <= 10 then -- 溜めてる最中、または5%の確率で
      return "foot"
    end
    return ""
  end
}

return Enemy