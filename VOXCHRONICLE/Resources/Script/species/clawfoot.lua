Enemy = {
  name = "クラーケンの足",
  imageName = "clawfoot",
  attack = 1,
  baseExp = 3,
  hasFrame = true,
  counter = 2,
  getSpeed = function(enemy, characterManager)
    return 0
  end,
  getFrequency = function(enemy, characterManager)
    return 1
  end,
  disableSkills = {},
  animationFrames = 4,
  performSkill = function(self)
    math.random(100)
    local rand = math.random(100)
    if rand <= 10 then
      return "foot"
    end
    return ""
  end
}

return Enemy