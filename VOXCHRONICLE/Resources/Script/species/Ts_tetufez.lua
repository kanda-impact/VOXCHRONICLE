Enemy = {
  name = "テツフェズ",
  imageName = "tetufez",
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
  description = [[
  ]],
  habitat = "",
  animationFrames = 6,
  performSkill = function(self)
  return ""
  end
}

return Enemy