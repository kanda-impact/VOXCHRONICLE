Enemy = {
  name = "波",
  imageName = "wave",
  attack = 10,
  baseExp = 0,
  hasFrame = true,
  counter = 1,
  getSpeed = function(enemy, characterManager)
    return 1
  end,
  getFrequency = function(enemy, characterManager)
    return 1
  end,
  disableSkills = {"attack", "magic", "knockback", "bow", "thunder", "slash"}, -- 全技を無効化する
  description = [[
  ]],
  habitat = "",
  animationFrames = 1,
  performSkill = function(self)
    return ""
  end
}

return Enemy