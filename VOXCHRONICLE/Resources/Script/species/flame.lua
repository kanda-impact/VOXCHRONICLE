Enemy = {
  name = "火の玉",
  imageName = "flame",
  attack = 2,
  baseExp = 6,
  hasFrame = true,
  counter = 2,
  getSpeed = function(enemy, characterManager)
    return 1
  end,
  getFrequency = function(enemy, characterManager)
    return 1
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