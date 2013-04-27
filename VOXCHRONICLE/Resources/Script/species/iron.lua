Enemy = {
  name = "鉄球",
  imageName = "iron",
  attack = 4,
  baseExp = 1,
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
いわゆるモーニングスター。かつては広く活躍したが、年代ものなのか、とってももろい。魔法生物といえども、歳には勝てないのだ
  ]],
  habitat = "",
  animationFrames = 1,
  performSkill = function(self)
  return ""
  end
}

return Enemy