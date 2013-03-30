Enemy = {
  name = "クリスタル",
  imageName = "cryst",
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
  気の遠くなるような年月を経て力を持った結晶石。
  自分のうまれた場所を守ろうとしている。
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
    return ""
  end
}

return Enemy