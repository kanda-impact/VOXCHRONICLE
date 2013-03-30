Enemy = {
  name = "鉄球",
  imageName = "iron",
  attack = 2,
  baseExp = 1,
  hasFrame = true,
  counter = 1,
  getSpeed = function(enemy, characterManager)
    return 1
  end,
  getFrequency = function(enemy, characterManager)
    return 2
  end,
  disableSkills = {},
  description = [[
  実は核エンジンで駆動しているらしい。
  ]],
  habitat = "",
  animationFrames = 1,
  performSkill = function(self)
  return ""
  end
}

return Enemy