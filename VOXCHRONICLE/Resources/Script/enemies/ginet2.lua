Enemy = {
  name = "ギネット",
  imageName = "ginet",
  level = 3,
  hp = 2,
  exp = 16,
  attack = 2,
  counter = 2,
  speed = 1,
  item = EnemyItemNone,
  animationFrames = 3,
  type = SkillTypeNormal,
  performSkill = function(self)
    return ""
  end
}

return Enemy