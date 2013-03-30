Enemy = {
  species = "wisp",
  level = 10,
  hp = 14,
  getExp = function(default)
      return 20
  end,
  item = EnemyItemBarrier,
  type = SkillTypeNormal,
}

return Enemy