Enemy = {
  species = "mimic",
  level = 10,
  hp = 12,
  getExp = function(default)
      return 15
  end,
  item = EnemyItemNone,
  type = SkillTypePhysical,
}

return Enemy