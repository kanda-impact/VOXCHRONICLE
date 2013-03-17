Enemy = {
  species = "toadstool",
  level = 10,
  hp = 30,
  getExp = function(default)
      return 15
  end,
  item = EnemyItemNone,
  type = SkillTypeMagical,
}

return Enemy
