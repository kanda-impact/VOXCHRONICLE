Enemy = {
  species = "save_cryst",
  level = 10,
  hp = 12,
  getExp = function(default)
      return 60
  end,
  item = EnemyItemShield,
  type = SkillTypeNormal,
}

return Enemy