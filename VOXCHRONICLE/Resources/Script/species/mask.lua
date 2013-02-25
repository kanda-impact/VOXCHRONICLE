Enemy = {
  name = "マスク",
  imageName = "mask",
  attack = 5,
  baseExp = 4,
  hasFrame = true,
  counter = 3,
  getSpeed = function(enemy, characterManager)
    return 1
  end,
  getFrequency = function(enemy, characterManager)
    return 2
  end,
  disableSkills = {},
  animationFrames = 4,
  performSkill = function(self)
  return ""
  end
}

return Enemy