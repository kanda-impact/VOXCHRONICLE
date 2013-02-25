Enemy = {
  name = "ジクー",
  imageName = "geek",
  attack = 1,
  baseExp = 1,
  hasFrame = false,
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