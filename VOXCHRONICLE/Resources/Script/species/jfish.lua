Enemy = {
  name = "クラゲ",
  imageName = "jfish",
  attack = 2,
  baseExp = 3,
  hasFrame = true,
  counter = 0,
  getSpeed = function(enemy, characterManager)
   local row = enemy:getRow()
    if row > 1 then -- 1列目より前に行ったとき、速度を0にします
      return 1
    end
    return 0
  end,
  getFrequency = function(enemy, characterManager)
    return 2
  end,
  disableSkills = {},
  description = [[
  クラゲのくらりん。足一つ一つに名前がある。
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