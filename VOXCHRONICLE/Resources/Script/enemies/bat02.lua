Enemy = {
  species = "bat",
  level = 20,
  hp = 12,
  getExp = function(default)
      return 5
  end,
  item = EnemyItemNone,
  type = SkillTypeNormal,
}

return Enemy