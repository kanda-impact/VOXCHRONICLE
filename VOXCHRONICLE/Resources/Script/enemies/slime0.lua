Enemy = {
  species = "slime",
  level = 1,
  hp = 1,
  getExp = function(default)
      return default
  end,
  item = EnemyItemNone,
  type = SkillTypeNormal,
}

return Enemy