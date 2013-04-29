Enemy = {
  name = "メウ",
  imageName = "flame",
  attack = 2,
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
  電子に火を与える試みの末うまれた。この事件が遠い未来
  の電子界に一大叙事詩を紡ぐ事になるが、それはまた別のお話。
  生息地：電脳世界　攻撃力：ふつう　移動：そこそこ
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
    return ""
  end
}

return Enemy