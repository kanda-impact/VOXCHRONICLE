math.randomseed(os.time())
Enemy = {
  name = "左ビット",
  imageName = "bit",
  attack = 50,
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
  左側のビット。すぐに倒されてしまうが右ビットの蘇生呪文で不死鳥の如く蘇る。
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
    return ""
  end
}

return Enemy