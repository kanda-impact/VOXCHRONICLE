Enemy = {
  name = "はっぱ",
  imageName = "leaf",
  attack = 0,
  baseExp = 6,
  hasFrame = true,
  counter = 0,
  getSpeed = function(enemy, characterManager)
    return 1
  end,
  getFrequency = function(enemy, characterManager)
    return 2
  end,
  disableSkills = {},
  description = [[
  木についていたわけではない。生まれた時から葉っぱ。
  秋の繁殖シーズンを過ぎれば、役目を終えた親世代は死に絶える。
  生息地：荒野ほか　攻撃力：そこそこ　移動：ふつう
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
  return ""
  end
}

return Enemy