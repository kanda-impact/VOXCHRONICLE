Enemy = {
  name = "スライム",
  imageName = "slime",
  attack = 2,
  baseExp = 5,
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
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
  return ""
  end
}

return Enemy