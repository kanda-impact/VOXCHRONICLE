Enemy = {
  name = "かわずたん",
  imageName = "kawaztan",
  attack = 3,
  baseExp = 6,
  hasFrame = true,
  counter = 2,
  getSpeed = function(enemy, characterManager)
    return 1
  end,
  getFrequency = function(enemy, characterManager)
    return 2
  end,
  description = [[
    みんなのアイドルかわずたんが黒魔法と光剣術を習得して参戦したぞ！
    『まとめてノシイカにしてやるケロ～☆』
  ]],
  habitat = "森林ほか",
  disableSkills = {},
  animationFrames = 4,
  performSkill = function(self)
    return ""
  end
}

return Enemy