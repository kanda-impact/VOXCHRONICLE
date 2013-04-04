Enemy = {
  name = "クラゲ",
  imageName = "jfish",
  attack = 1,
  baseExp = 3,
  hasFrame = true,
  counter = 0,
  getSpeed = function(enemy, characterManager)
    return 1
  end,
  getFrequency = function(enemy, characterManager)
    return 2
  end,
  disableSkills = {},
  description = [[
  真っ暗な深海をポツリポツリと照らす大クラゲ。
  時折集団で謎の幾何学模様を形成したり、その生態は不明。
  トメゾラとは遠い親戚。
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
    return ""
  end
}

return Enemy