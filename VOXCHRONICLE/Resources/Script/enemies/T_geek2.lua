Enemy = {
  species = "Ts_geek",
  level = 10,
  hp = 3,
  attack = 1,
  getExp = function(default)
      return 0
  end,
  item = EnemyItemBarrier,
  type = SkillTypeNormal,
}

return Enemy
