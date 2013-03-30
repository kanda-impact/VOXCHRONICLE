Enemy = {
  name = "宇宙生物",
  imageName = "exob",
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
  description = [[
  あまねく宇宙に普遍的に存在している、
  故郷の星をもたない謎生命。
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
    return ""
  end
}

return Enemy