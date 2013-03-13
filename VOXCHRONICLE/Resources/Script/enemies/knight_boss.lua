Enemy = {
  species = "knight",
  level = 30,
  hp = 120,
  getExp = function(default)
      return default
  end,
  item = EnemyItemNone,
  type = SkillTypeNormal,
}

return Enemy
