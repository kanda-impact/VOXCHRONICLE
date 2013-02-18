Enemy = {
  species = "dragon",
  level = 24,
  hp = 8,
  getExp = function(default)
      return default
  end,
  item = EnemyItemShield,
  type = SkillTypeNormal,
}

return Enemy