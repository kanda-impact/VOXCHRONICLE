Enemy = {
  name = "ルーシャルナー",
  imageName = "whale",
  attack = 12,
  baseExp = 3,
  hasFrame = true,
  counter = 2,
  getSpeed = function(enemy, characterManager)
    return 1
  end,
  getFrequency = function(enemy, characterManager)
    return 3
  end,
  disableSkills = {},
  description = [[
  陸に上がり海に帰った深海生物。
  彼らの歌ははるか遠い遠い彼方までひびくため、
  だいたいは声はすれど姿は見えない。
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
    return ""
  end
}

return Enemy