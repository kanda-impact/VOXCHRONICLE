Enemy = {
  name = "レセス",
  imageName = "jfish",
  attack = 2,
  baseExp = 3,
  hasFrame = true,
  counter = 0,
  getSpeed = function(enemy, characterManager)
   local row = enemy:getRow()
    if row > 0 then -- 1列目より前に行ったとき、速度を0にします
      return 1
    end
    return 0
  end,
  getFrequency = function(enemy, characterManager)
    return 3
  end,
  disableSkills = {},
  description = [[
  真っ暗な深海をポツリポツリと照らす大クラゲ。
  時折集団で謎の幾何学模様を形成したり、その生態は不明。
  トメゾラという親戚クラゲもいる
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