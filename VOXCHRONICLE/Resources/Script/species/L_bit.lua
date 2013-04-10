math.randomseed(os.time())
Enemy = {
  name = "左ビット",
  imageName = "bit",
  attack = 20,
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
    local r = math.random(100)
    if r < 70 then
      return "beam"
    end
    return ""
  end
}

return Enemy