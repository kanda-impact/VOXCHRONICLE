Enemy = {
  species = "bat",
  level = 10,
  hp = 15,
  getExp = function(default)
      return 20
  end,
  item = EnemyItemNone,
  type = SkillTypeNormal,
}

return Enemy