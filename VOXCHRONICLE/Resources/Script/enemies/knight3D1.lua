Enemy = {
  species = "knight",
  level = 30,
  hp = 72,
  getExp = function(default)
      return 15
  end,
  item = EnemyItemNone,
  type = SkillTypeMagical,
}

return Enemy
