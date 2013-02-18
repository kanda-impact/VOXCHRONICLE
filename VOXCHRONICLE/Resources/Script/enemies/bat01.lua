
Enemy = {
  species = "bat",
  level = 10,
  hp = 12,
  getExp = function(default)
      return default
  end,
  item = EnemyItemNone,
  type = SkillTypeMagical,
}

return Enemy