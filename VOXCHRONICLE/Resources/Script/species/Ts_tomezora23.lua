Enemy = {
  name = "トメゾラ",
  imageName = "tomezora",
  attack = 0,
  baseExp = 0,
  hasFrame = false,
  counter = 0,
  getSpeed = function(enemy, characterManager)
    local row = enemy:getRow()
    if row == 0 then
      return 0
    end
    return 1
  end,
  getFrequency = function(enemy, characterManager)
    return 2
  end,
  disableSkills = {},
  description = [[
２本の長い触手が電極の役割を果たしている。たくさん繋がるとその分強力になる。
]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
    local row = self:getRow()
    if row == 0 then
      return "direct_attack"
    end
    return ""
  end}

return Enemy