Enemy = {
  name = "砦",
  imageName = "fortress",
  attack = 50,
  baseExp = 0,
  hasFrame = true,
  counter = 0,
  getSpeed = function(enemy, characterManager)
    local row = enemy:getRow()
    if row > 0 then
      return 1
    end
    return 0
  end,
  getFrequency = function(enemy, characterManager)
    return 5
  end,
  disableSkills = {"knockback"},
  description = [[
  古代の超技術で作られた。なんか歩く城。
  硬いけど　古いから　突っ込んでくるだけ。
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
    local row = self:getRow()
    if row == 0 then
      return "direct_attack"
    end
    return ""
  end
}

return Enemy