Enemy = {
  name = "ナイト",
  imageName = "knight",
  level = 10,
  hp = 20,
  exp = 100,
  attack = 1,
 minRow = 4,
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
