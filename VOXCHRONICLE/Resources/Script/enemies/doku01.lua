Enemy = {
  species = "toadstool",
  level = 5,
  hp = 12,
  getExp = function(default)
      return 15
  end,
  item = EnemyItemNone,
  type = SkillTypeNormal,
}

return Enemy