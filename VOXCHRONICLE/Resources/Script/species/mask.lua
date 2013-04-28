Enemy = {
  name = "メシャベンマー",
  imageName = "mask",
  attack = 6,
  baseExp = 4,
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
  古代の呪術師が作ったマスク。
  マスクが浮いてるように見えるが、見えない体もある。
  生息地：遺跡　攻撃力：そこそこ　移動：ふつう
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
  return ""
  end
}

return Enemy