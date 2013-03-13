Enemy = {
  name = "右かぎ爪pl",
  imageName = "R_plclaw",
  attack = 1,
  baseExp = 6,
  hasFrame = true,
  counter = 0,
  getSpeed = function(enemy, characterManager)
    return 0
  end,
  getFrequency = function(enemy, characterManager)
    return 1
  end,
  disableSkills = {"knockback"},
  animationFrames = 4,
  performSkill = function(self)
    return ""
  end
}

return Enemy