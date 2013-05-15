Enemy = {
  name = "ドラゴンキッズ",
  imageName = "dragon",
  attack = 12,
  baseExp = 6,
  hasFrame = true,
  counter = 2,
  getSpeed = function(enemy, characterManager)
    return 1
  end,
  getFrequency = function(enemy, characterManager)
    return 2
  end,
  disableSkills = {},
  description = [[
パワーも一丁前。炎が吐ける所も一丁前。
ふてぶてしい態度も一丁前。でもまだ飛べない。
生息地：炭鉱ほか　攻撃力：そこそこ　移動：ふつう
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
    return ""
  end
}

return Enemy