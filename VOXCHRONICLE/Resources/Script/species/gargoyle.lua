Enemy = {
  name = "ゴイルゥガ",
  imageName = "gargoyle",
  attack = 12,
  baseExp = 10,
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
石の彫像に兵士の魂をこめて作られた。当初は責務から侵入者を攻撃していたが、
今は動けない事に飽きて侵入者にちょっかいを掛ける。
生息地：遺跡ほか　攻撃力：たかい　移動：ふつう
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
  return ""
  end
}

return Enemy