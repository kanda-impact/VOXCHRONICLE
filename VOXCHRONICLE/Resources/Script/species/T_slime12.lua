Enemy = {
  name = "スライム",
  imageName = "slime",
  attack = 0,
  baseExp = 5,
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
  自由を手にした誰かのおやつ。
  お目目をどこかに失くしがちなので、
  見つけたら戻してあげて。
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
  return ""
  end
}

return Enemy