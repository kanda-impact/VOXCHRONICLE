Enemy = {
  name = "ちょうちょ",
  imageName = "moth",
  attack = 0,
  baseExp = 10,
  hasFrame = true,
  counter = 1,
  getSpeed = function(enemy, characterManager)
    return 1

  end,
  getFrequency = function(enemy, characterManager)
    return 2
  end,
  disableSkills = {},
  description = [[
  ポンポンの粉を散らされると死んでしまう儚い命。
  稀に集団発生してはオクスとラスカと誰かを大いに苦しめる。
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
  return ""
  end
}

return Enemy