Enemy = {
  name = "ジクーキラー",
  imageName = "moth",
  attack = 5,
  baseExp = 10,
  hasFrame = true,
  counter = 1,
  getSpeed = function(enemy, characterManager)
    return 1

  end,
  getFrequency = function(enemy, characterManager)
    return 2
  end,
  disableSkills = {},
  description = [[
ポンポンの粉を散らされると死んでしまう儚い命。ジクーの天敵。別に強くはないが蝶の嫌いな人にはツラいかも。
生息地：森林ほか　攻撃力：そこそこ　移動：ふつう
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
  return ""
  end
}

return Enemy