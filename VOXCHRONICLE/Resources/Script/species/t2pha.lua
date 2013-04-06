Enemy = {
  name = "ファージィ",
  imageName = "t2pha",
  attack = 1,
  baseExp = 6,
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
  生物と無生物の間で揺れる構造体。
  生物に対して無類の強さだが、電子生命に負ける。
  電子生命にはやる気がないので実質敵なし。
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
    return ""
  end
}

return Enemy