Enemy = {
  name = "テツフェズ",
  imageName = "tetufez",
  attack = 1,
  baseExp = 1,
  hasFrame = false,
  counter = 1,
  getSpeed = function(enemy, characterManager)
    return 1
  end,
  getFrequency = function(enemy, characterManager)
    return 2
  end,
  disableSkills = {},
  description = [[
  魔物であるか人工的な魔法生物であるか
  諸説あるがわかっていない。叩くといい音がする。
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
  return ""
  end
}

return Enemy