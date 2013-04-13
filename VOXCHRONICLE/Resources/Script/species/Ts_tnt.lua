Enemy = {
  name = "ティエヌティ",
  imageName = "ttn",
  attack = 1,
  baseExp = 1,
  hasFrame = false,
  counter = 2,
  getSpeed = function(enemy, characterManager)
    return 1
  end,
  getFrequency = function(enemy, characterManager)
    return 1
  end,
  disableSkills = {},
  description = [[
  雪原でしばしば目撃される。原始的で合理的な巨体の持ち主。
  ]],
  habitat = "",
  animationFrames = 5,
  performSkill = function(self)
  return ""
  end
}

return Enemy