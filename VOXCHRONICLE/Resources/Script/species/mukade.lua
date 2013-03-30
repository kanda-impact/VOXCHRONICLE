Enemy = {
  name = "ムカデ",
  imageName = "mukade",
  attack = 2,
  baseExp = 1,
  hasFrame = true,
  counter = 1,
  getSpeed = function(enemy, characterManager)
   local row = enemy:getRow()
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