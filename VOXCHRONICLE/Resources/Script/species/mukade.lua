Enemy = {
  name = "ムカデ",
  imageName = "mukade",
  attack = 2,
  baseExp = 1,
  hasFrame = true,
  counter = 1,
  getSpeed = function(enemy, characterManager)
   local row = enemy:getRow()
    if row > 3 then -- 4列目より前に行ったとき、速度を0にします
      return 2
    elseif row > 0 then
      return 1
    end
    return 0
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
    local row = self:getRow()
    if row == 0 then
      return "direct_attack"
    end
    return ""
  end
}

return Enemy