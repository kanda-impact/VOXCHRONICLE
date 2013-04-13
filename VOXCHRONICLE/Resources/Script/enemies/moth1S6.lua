Enemy = {
  species = "moth",
  level = 10,
  hp = 9,
  getExp = function(default)
      return 10
  end,
  item = EnemyItemBarrier,
  type = SkillTypeNormal,
}

return Enemy