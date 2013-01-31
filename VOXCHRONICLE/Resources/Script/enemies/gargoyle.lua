Enemy = {
  name = "ガーゴイル",
  imageName = "gargoyle",
  level = 1,
  hp = 4,
  exp = 20,
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