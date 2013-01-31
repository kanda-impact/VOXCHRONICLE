Enemy = {
  name = "毒キノコ",
  imageName = "toadstool",
  level = 1,
  hp = 1,
  exp = 5,
  attack = 1,
  hasFrame = true,
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