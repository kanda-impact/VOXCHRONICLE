Enemy = {
  name = "マアシミー",
  imageName = "typhoon",
  attack = 8,
  baseExp = 1,
  hasFrame = true,
  counter = 3,
  getSpeed = function(enemy, characterManager)
    return 1
  end,
  getFrequency = function(enemy, characterManager)
    return 2
  end,
  disableSkills = {},
  description = [[
  つむじ風が集まった台風のこども。時折キウーユが混じって遊んでいたりする。
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
  return ""
  end
}

return Enemy