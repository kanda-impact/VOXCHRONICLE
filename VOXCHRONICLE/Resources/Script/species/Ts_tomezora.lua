Enemy = {
  name = "トメゾラ",
  imageName = "tomezora",
  attack = 0,
  baseExp = 0,
  hasFrame = false,
  counter = 0,
  getSpeed = function(enemy, characterManager)
    return 1
  end,
  getFrequency = function(enemy, characterManager)
    return 2
  end,
  disableSkills = {},
  description = [[
２本の長い触手が電極の役割を果たしている。たくさん繋がるとその分強力になる。
]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
  return ""
  end
}

return Enemy