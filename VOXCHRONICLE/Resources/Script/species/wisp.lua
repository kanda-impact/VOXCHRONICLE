Enemy = {
  name = "ウィートパペイ",
  imageName = "wisp",
  attack = 9,
  baseExp = 1,
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
  かつてここで信仰されていた光の力の痕跡が、姿を持って立ちのぼった。
  闇の勢力と終わりのない闘いを永久に続けている。
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
  return ""
  end
}

return Enemy