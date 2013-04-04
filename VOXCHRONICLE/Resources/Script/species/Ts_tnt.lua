Enemy = {
  name = "ティエヌティ",
  imageName = "ttn",
  attack = 1,
  baseExp = 1,
  hasFrame = false,
  counter = 1,
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
  animationFrames = 7,
  performSkill = function(self)
  return ""
  end
}

return Enemy