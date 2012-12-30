Enemy = {
  name = "スライム",
  imageName = "slime",
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
  choiceSkill = function(self)
    return nil
  end
}
