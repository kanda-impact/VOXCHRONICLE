Enemy = {
  name = "鉄球",
  imageName = "iron",
  level = 10,
  hp = 1,
  exp = 0,
  hasFrame = true,
  attack = 3,
  counter = 1,
  speed = 2,
  item = EnemyItemNone,
  animationFrames = 1,
  type = SkillTypeNormal,
  performSkill = function(self)
    return ""
  end
}

return Enemy
