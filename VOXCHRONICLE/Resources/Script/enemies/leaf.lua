Enemy = {
  name = "はっぱ",
  imageName = "leaf",
  level = 3,
  hp = 2,
  exp = 8,
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