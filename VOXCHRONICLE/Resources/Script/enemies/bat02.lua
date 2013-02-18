Enemy = {
  species = "bat",
  level = 20,
  hp = 12,
  getExp = function(default)
      return default
  end,
  item = EnemyItemNone,
  type = SkillTypeNormal,
}

return Enemy