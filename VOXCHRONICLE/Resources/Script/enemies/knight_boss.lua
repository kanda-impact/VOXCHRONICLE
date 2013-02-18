Enemy = {
  species = "knight",
  level = 30,
  hp = 150,
  getExp = function(default)
      return default
  end,
  item = EnemyItemNone,
  type = SkillTypeNormal,
}

return Enemy
