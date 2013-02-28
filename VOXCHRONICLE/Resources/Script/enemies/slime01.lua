Enemy = {
  species = "slime",
  level = 7,
  hp = 6,
  getExp = function(default)
      return 12
  end,
  item = EnemyItemNone,
  type = SkillTypePhysical,
}

return Enemy