Enemy = {
  species = "knight",
  level = 1,
  hp = 5,
  getExp = function(default)
      return default
  end,
  item = EnemyItemNone,
  type = SkillTypeNormal,
}

return Enemy
