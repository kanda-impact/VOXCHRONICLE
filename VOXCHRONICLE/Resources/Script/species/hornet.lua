Enemy = {
  name = "オオリー",
  imageName = "hornet",
  attack = 4,
  baseExp = 1,
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
  働きバチではない。彼らは誇り高きノマドワーカー。
  しかし巣畜時代の元同僚に対する心中は複雑。
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
  return ""
  end
}

return Enemy