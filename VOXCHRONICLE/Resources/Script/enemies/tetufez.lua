Enemy = {
  name = "ツテフェズ",
  imageName = "tetufez",
  level = 4,
  hp = 1,
  exp = 12,
  attack = 3,
  counter = 3,
  speed = 1,
  item = EnemyItemNone,
  animationFrames = 8,
  type = SkillTypeNormal,
  performSkill = function(self)
    return ""
  end
}

return Enemy