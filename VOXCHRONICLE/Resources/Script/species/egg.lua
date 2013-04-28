Enemy = {
  name = "ギヤンー",
  imageName = "egg",
  attack = 2,
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
  電子に自己増殖機能を与える試みの末うまれた。
  転ぶまでは増えつづける。
  生息地：電脳世界　攻撃力：ふつう　移動：そこそこ
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
    return ""
  end
}

return Enemy