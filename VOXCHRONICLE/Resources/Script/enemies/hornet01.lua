Enemy = {
  species = "hornet",
  level = 10,
  hp = 6,
  getExp = function(default)
      return default
  end,
  item = EnemyItemNone,
  type = SkillTypeNormal,
}

return Enemy