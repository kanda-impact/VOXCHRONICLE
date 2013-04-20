Enemy = {
  species = "coin",
  level = 1,
  hp = 12,
  getExp = function(default)
      return 10
  end,
  item = EnemyItemNone,
  type = SkillTypeMagical,
}

return Enemy