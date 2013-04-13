Enemy = {
  name = "ンガシィ",
  imageName = "kani",
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
  電子に危機回避を与える試みの末うまれた。
  下方向からの衝撃をおそれているようだ。
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
    return ""
  end
}

return Enemy