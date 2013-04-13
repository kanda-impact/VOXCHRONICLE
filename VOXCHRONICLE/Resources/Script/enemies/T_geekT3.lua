Enemy = {
  species = "Ts_geek",
  level = 10,
  hp = 9,
  getExp = function(default)
      return 0
  end,
  attack = 3,
  item = EnemyItemShield,
  type = SkillTypeNormal,
}

return Enemy