Enemy = {
  name = "ジク—",
  imageName = "geek",
  level = 8,
  hp = 1,
  exp = 15,
  attack = 1,
  counter = 1,
  speed = 2,
  item = EnemyItemShield,
  animationFrames = 4,
  type = SkillTypeNormal,
  performSkill = function(self)
    return ""
  end
}

return Enemy