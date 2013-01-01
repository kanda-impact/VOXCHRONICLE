Enemy = {
  name = "タイフーン",
  imageName = "typhoon",
  level = 1,
  hp = 1,
  exp = 5,
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