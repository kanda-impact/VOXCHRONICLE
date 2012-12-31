Enemy = {
  name = "ナイト",
  imageName = "knight",
  level = 10,
  hp = 20,
  exp = -1,
  attack = 1,
  minRow = 4,
  hasFrame = true,
  counter = 1,
  speed = 2,
  item = EnemyItemNone,
  animationFrames = 4,
  type = SkillTypeNormal,
  performSkill = function(self)
    -- 最前列にいるとき、常に鉄球投げをする
    if self:getRow() <= 4 then
      return "ironball"
    end
    return ""
  end
}

return Enemy