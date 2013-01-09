Enemy = {
  name = "スライム",
  imageName = "slime",
  level = 5,
  hp = 3,
  exp = 10,
  attack = 1,
  hasFrame = true,
  counter = 1,
  speed = 2,
  item = EnemyItemNone,
  animationFrames = 4,
  type = SkillTypePhysical,
  performSkill = function(self)
    return ""
  end
}

return Enemy