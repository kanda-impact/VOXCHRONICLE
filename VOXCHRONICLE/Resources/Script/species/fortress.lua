Enemy = {
  name = "砦",
  imageName = "fortress",
  attack = 50,
  baseExp = 0,
  hasFrame = true,
  counter = 0,
  getSpeed = function(enemy, characterManager)
    return 1
  end,
  getFrequency = function(enemy, characterManager)
    return 5
  end,
  disableSkills = {"knockback"},
  animationFrames = 4,
  performSkill = function(self)
    return ""
  end
}

return Enemy