Enemy = {
  name = "ハートォ",
  imageName = "heart",
  attack = 1,
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
  電子に生命を与える試みの末うまれた。
  われわれは　どこからきて　どこへ　ゆくのか
  生息地：電脳世界　攻撃力：よわい　移動：ふつう
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
    return ""
  end
}

return Enemy