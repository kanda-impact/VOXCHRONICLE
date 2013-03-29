Enemy = {
  species = "mimic",
  level = 10,
  hp = 14,
  getExp = function(default)
      return 12
  end,
  item = EnemyItemShield,
  type = SkillTypeNormal,
}

return Enemy