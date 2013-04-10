math.randomseed(os.time())
Enemy = {
  name = "右ビット",
  imageName = "bit",
  attack = 100,
  baseExp = 1,
  hasFrame = true,
  counter = 0,
  getSpeed = function(enemy, characterManager)
    return 0
  end,
  getFrequency = function(enemy, characterManager)
    return 1
  end,
  disableSkills = {"knockback"},
  description = [[
  右側のビット。その正体は真の究極生命体＜＞コアだった、ということはなく、ただの中間管理職。いつかラスボスになれる日を夢見て職務を全うしている
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
    return ""
  end
}

return Enemy