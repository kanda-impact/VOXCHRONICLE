Enemy = {
  name = "エクソブ",
  imageName = "exob",
  attack = 5,
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
  あまねく宇宙に普遍的に存在している、
  故郷の星をもたない謎生命。
  生息地：宙域　攻撃力：そこそこ　移動：ふつう
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
    return ""
  end
}

return Enemy