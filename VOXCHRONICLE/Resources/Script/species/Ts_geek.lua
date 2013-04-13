Enemy = {
  name = "ジクー",
  imageName = "geek",
  attack = 0,
  baseExp = 1,
  hasFrame = false,
  counter = 0,
  getSpeed = function(enemy, characterManager)
    return 1
  end,
  getFrequency = function(enemy, characterManager)
    return 1
  end,
  disableSkills = {},
  description = [[
 魔物であるか人工的な魔法生物であるか諸説あるがわかっていない。
 機嫌によって点滅のパターンが変わる。
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
  return ""
  end
}

return Enemy