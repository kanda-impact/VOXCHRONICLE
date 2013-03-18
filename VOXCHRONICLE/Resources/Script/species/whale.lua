Enemy = {
  name = "クジラ",
  imageName = "whale",
  attack = 1,
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
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
    return ""
  end
}

return Enemy