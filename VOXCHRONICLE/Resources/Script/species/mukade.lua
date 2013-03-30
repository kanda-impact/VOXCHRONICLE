Enemy = {
  name = "ムカデ",
  imageName = "mukade",
  attack = 1,
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
  節１個から全身を再生できるのでどんどん増える。
  １匹見たら３０匹いると思え。
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
  return ""
  end
}

return Enemy