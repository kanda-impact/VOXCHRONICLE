Enemy = {
  name = "エヌティ",
  imageName = "nisok",
  attack = 8,
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
  電子に自由を与える試みの末うまれた。
  歩く事が目的であって行く宛はない。
  生息地：電脳世界　攻撃力：そこそこ　移動：ふつう
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
    return ""
  end
}

return Enemy