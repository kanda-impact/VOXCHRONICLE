Enemy = {
  name = "タイフーン",
  imageName = "typhoon",
  level = 5,
  hp = 3,
  exp = 10,
  hasFrame = true,
  attack = 1,
  counter = 1,
  speed = 2,
  item = EnemyItemNone,
  animationFrames = 4,
  type = SkillTypeMagical,
  performSkill = function(self)
    return ""
  end
}

return Enemy