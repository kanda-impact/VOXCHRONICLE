Enemy = {
  species = "knight",
  level = 30,
  hp = 50,
  getExp = function(default)
      return 15
  end,
  attack = 12,
  item = EnemyItemNone,
  type = SkillTypeMagical,
}

return Enemy
