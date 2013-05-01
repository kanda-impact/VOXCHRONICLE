Enemy = {
  name = "ビトー",
  imageName = "slime",
  attack = 2,
  baseExp = 5,
  hasFrame = true,
  counter = 0,
  getSpeed = function(enemy, characterManager)
    return 1
  end,
  getFrequency = function(enemy, characterManager)
    return 2
  end,
  disableSkills = {},
  description = [[
自由を手にした誰かのおやつ。お目目をどこかに失くしがちなので、見つけたら戻してあげて。
生息地：荒野ほか　攻撃力：ふつう　移動：ふつう
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
  return ""
  end
}

return Enemy