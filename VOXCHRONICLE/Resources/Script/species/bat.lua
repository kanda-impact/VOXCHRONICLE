Enemy = {
  name = "コウモリ",
  imageName = "bat",
  attack = 2,
  baseExp = 3,
  hasFrame = true,
  counter = 2,
  getSpeed = function(enemy, characterManager)
    return 1
  end,
  getFrequency = function(enemy, characterManager)
    return 2
  end,
  disableSkills = {},
  description = [[
  血を３００ｃｃ吸ったりしない割合安全なコウモリ。陽気で騒々しい。
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
    return ""
  end
}

return Enemy