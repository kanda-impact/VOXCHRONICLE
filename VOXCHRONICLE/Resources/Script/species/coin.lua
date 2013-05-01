Enemy = {
  name = "ツーテ",
  imageName = "coin",
  attack = 3,
  baseExp = 6,
  hasFrame = true,
  counter = 0,
  getSpeed = function(enemy, characterManager)
    return 1
  end,
  getFrequency = function(enemy, characterManager)
    return 1
  end,
  disableSkills = {},
  description = [[
電子に通貨の概念を与える試みの末うまれた。
１００枚集めても１UPしない。
生息地：電脳世界　攻撃力：ふつう　移動：そこそこ
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
    return ""
  end
}

return Enemy