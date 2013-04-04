Enemy = {
  name = "パンジーさん",
  imageName = "flower",
  attack = 2,
  baseExp = 3,
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
  ハミングしていないと光合成できないので、
  常にハミングしてる。最近のパンジーさん界隈ではボッサが来てる。
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
  return ""
  end
}

return Enemy