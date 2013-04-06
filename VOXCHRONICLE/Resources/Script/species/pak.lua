Enemy = {
  name = "ユゥーンデュ",
  imageName = "pak",
  attack = 4,
  baseExp = 6,
  hasFrame = true,
  counter = 1,
  getSpeed = function(enemy, characterManager)
    return 1
  end,
  getFrequency = function(enemy, characterManager)
    return 1
  end,
  disableSkills = {},
  description = [[
  電子に光合成能力を与える試みの末うまれた。
  光合成より他のいきものを捕食した方が効率がいいので使ってない。
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
    return ""
  end
}

return Enemy