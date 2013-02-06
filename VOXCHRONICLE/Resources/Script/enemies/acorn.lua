Enemy = {
  name = "ドングリ",
  imageName = "acorn",
  level = 1,
  hp = 1,
  exp = 5,
  hasFrame = true,
  attack = 1,
  counter = 1,
  speed = 2,
  item = EnemyItemNone,
  animationFrames = 4,
  type = SkillTypeNormal,
  performSkill = function(self)
    return ""
  end
}

return Enemy