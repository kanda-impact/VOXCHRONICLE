Enemy = {
  name = "ドングリィ",
  imageName = "acorn",
  attack = 3,
  baseExp = 6,
  hasFrame = true,
  counter = 1,
  getSpeed = function(enemy, characterManager)
    return 1
  end,
  getFrequency = function(enemy, characterManager)
    return 2
  end,
  description = [[
    どう見てもマツボックリです、本当にありがとうございました。
    確かにコロコロしながらやってくるが、彼らはY軸回転を採用したようである。
  ]],
  habitat = "森林ほか",
  disableSkills = {},
  animationFrames = 4,
  performSkill = function(self)
    return ""
  end
}

return Enemy