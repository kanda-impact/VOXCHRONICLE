Enemy = {
  name = "T2ファージ",
  imageName = "t2pha",
  attack = 1,
  baseExp = 6,
  hasFrame = true,
  counter = 2,
  getSpeed = function(enemy, characterManager)
    return 1
  end,
  getFrequency = function(enemy, characterManager)
    return 2
  end,
  disableSkills = {},
  disableSkills = {},
  animationFrames = 4,
  performSkill = function(self)
    return ""
  end
}

return Enemy