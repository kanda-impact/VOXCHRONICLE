Enemy = {
  name = "ウィスプ",
  imageName = "wisp",
  level = 1,
  hp = 1,
  exp = 7,
  attack = 1,
  hasFrame = true,
  counter = 1,
  speed = 2,
  item = EnemyItemNone,
  animationFrames = 4,
  type = SkillTypeMagical,
  performSkill = function(self)
    return ""
  end
}

return Enemy