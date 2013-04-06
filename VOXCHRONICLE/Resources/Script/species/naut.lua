Enemy = {
  name = "ボゥチャー",
  imageName = "naut",
  attack = 6,
  baseExp = 3,
  hasFrame = true,
  counter = 1,
  getSpeed = function(enemy, characterManager)
    return 1
  end,
  getFrequency = function(enemy, characterManager)
    return 3
  end,
  disableSkills = {},
  description = [[
  太古の昔から姿の変わらない生きた化石。
  頑丈な殻で生存競争から離脱。
  レセスの周囲に集まって井戸端会議をする。
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
    return ""
  end
}

return Enemy