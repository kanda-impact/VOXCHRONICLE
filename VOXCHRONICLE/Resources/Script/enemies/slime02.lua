Enemy = {
  species = "slime",
  level = 10,
  hp = 9,
  getExp = function(default)
      return 5
  end,
  item = EnemyItemNone,
  type = SkillTypePhysical,
}

return Enemy