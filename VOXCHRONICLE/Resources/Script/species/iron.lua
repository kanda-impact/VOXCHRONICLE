Enemy = {
  name = "鉄球",
  imageName = "iron",
  attack = 4,
  baseExp = 1,
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
かつては世界中で活躍した鉄球の末裔。 鉄球の割に脆いのは年代物だからか。歳には勝てないね。
  ]],
  habitat = "",
  animationFrames = 1,
  performSkill = function(self)
  return ""
  end
}

return Enemy