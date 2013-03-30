Enemy = {
  name = "惑星",
  imageName = "planet",
  attack = 1,
  baseExp = 6,
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
  天球を惑う迷子の星。
  恒星をみつけては他の惑星と一緒にまとわりつきたがる。
  さみしがり。
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
    return ""
  end
}

return Enemy