Enemy = {
  name = "ギネード",
  imageName = "ginet",
  attack = 0,
  baseExp = 1,
  hasFrame = false,
  counter = 1,
  getSpeed = function(enemy, characterManager)
    return 1
  end,
  getFrequency = function(enemy, characterManager)
    return 2
  end,
  disableSkills = {},
  description = [[
  なりふり構わずとりあえず噛み付く事がコミュニケーションないぬ。
  しかし、実はねこなのではないかという情報もある。
  ]],
  habitat = "",
  animationFrames = 3,
  performSkill = function(self)
  return ""
  end
}

return Enemy