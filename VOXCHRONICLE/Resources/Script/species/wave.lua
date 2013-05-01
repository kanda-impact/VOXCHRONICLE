Enemy = {
  name = "ザブゥー",
  imageName = "wave",
  attack = 10,
  baseExp = 0,
  hasFrame = true,
  counter = 3,
  getSpeed = function(enemy, characterManager)
    return 1
  end,
  getFrequency = function(enemy, characterManager)
    return 1
  end,
  disableSkills = {"attack", "magic", "knockback", "bow", "thunder", "slash"}, -- 全技を無効化する
  description = [[
自然の驚異。ＢＩＧＷＡＶＥ。
翻弄されたくなければ、このうねりを越えて行け。
生息地：深海ほか　攻撃力：つよい　移動：そこそこ
  ]],
  habitat = "",
  animationFrames = 1,
  performSkill = function(self)
    return ""
  end
}

return Enemy