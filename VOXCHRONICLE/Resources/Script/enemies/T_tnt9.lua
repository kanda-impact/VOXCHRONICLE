Enemy = {
  species = "Ts_tnt",
  level = 10,
  hp = 30,
  attack = 2,
  getExp = function(default)
      return 60
  end,
  item = EnemyItemNone,
  type = SkillTypeNormal
}

return Enemy
