math.randomseed(os.time())
Enemy = {
  name = "ラスボス第1形態",
  imageName = "flast",
  attack = 20,
  baseExp = 1,
  hasFrame = true,
  counter = 0,
  width = 256,
  height = 170.75,
  getSpeed = function(enemy, characterManager)
    return 0
  end,
  getFrequency = function(enemy, characterManager)
    return 1
  end,
  disableSkills = {"knockback"},
  description = [[
  ラスボスだよー
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
    math.random(100)
    local rand = math.random(100)
    if rand < 50 then
      return "warp"
    elseif rand < 60 then
      return "cure_skill"
    end
    return ""
  end
}

return Enemy