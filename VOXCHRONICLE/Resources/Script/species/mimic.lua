Enemy = {
  name = "ミミック",
  imageName = "mimic",
  attack = 4,
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
  animationFrames = 4,
  performSkill = function(self)
  return ""
  end
}

return Enemy