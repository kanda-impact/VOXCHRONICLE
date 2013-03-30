Enemy = {
  name = "コイン",
  imageName = "coin",
  attack = 3,
  baseExp = 6,
  hasFrame = true,
  counter = 2,
  getSpeed = function(enemy, characterManager)
    return 1
  end,
  getFrequency = function(enemy, characterManager)
    return 1
  end,
  disableSkills = {},
  description = [[
電子に通貨の概念を与える試みの末うまれた。
100枚集めたら１UPしない。
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
    return ""
  end
}

return Enemy