Enemy = {
  name = "ネハココ",
  imageName = "toadstool",
  attack = 7,
  baseExp = 5,
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
  ゴホゴホ。これ病気じゃないんですよゴホゴホ。
  うつらないから大丈夫ですからゴホゴホ。
  でもなんか虫とか死ぬんですよねゴホゴホ。
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
  return ""
  end
}

return Enemy