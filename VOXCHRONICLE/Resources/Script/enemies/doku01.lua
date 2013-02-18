Enemy = {
  species = "toadstool",
  level = 5,
  hp = 15,
  getExp = function(default)
      return default
  end,
  item = EnemyItemNone,
  type = SkillTypeNormal,
}

return Enemy