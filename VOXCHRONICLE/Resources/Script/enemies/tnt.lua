Enemy = {
  name = "ティエヌティ",
  imageName = "tnt",
  level = 5,
  hp = 3,
  exp = 18,
  attack = 3,
  counter = 0,
  speed = 3,
  item = EnemyItemNone,
  animationFrames = 7,
  type = SkillTypeNormal,
  performSkill = function(self)
    return ""
  end
}

return Enemy