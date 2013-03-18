Enemy = {
  name = "ドングリ",
  imageName = "acorn",
  attack = 3,
  baseExp = 6,
  hasFrame = true,
  counter = 2,
  getSpeed = function(enemy, characterManager)
    return 1
  end,
  getFrequency = function(enemy, characterManager)
    return 2
  end,
  description = [[
    どう見てもドングリです、本当にありがとうございました。
  ]],
  habitat = "森林ほか",
  disableSkills = {},
  animationFrames = 4,
  performSkill = function(self)
    return ""
  end
}

return Enemy