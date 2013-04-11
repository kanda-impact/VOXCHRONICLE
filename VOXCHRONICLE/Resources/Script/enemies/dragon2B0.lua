Enemy = {
  species = "dragon",
  level = 10,
  hp = 42,
  getExp = function(default)
      return 60
  end,
  item = EnemyItemNone,
  type = SkillTypeNormal,
}

return Enemy