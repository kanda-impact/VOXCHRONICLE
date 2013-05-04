Enemy = {
  name = "ミミツクー",
  imageName = "mimic",
  attack = 4,
  baseExp = 5,
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
擬態がバレないよう、宝箱の流行を追い求めて日々進化を続ける進化の奇跡の産物。流行を追わなくなったら、冒険者に狩られてしまうさだめ。
生息地：遺跡ほか　攻撃力：つよい　移動：ふつう
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
  return ""
  end
}

return Enemy