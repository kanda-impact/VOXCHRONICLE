Enemy = {
  species = "egg",
  level = 1,
  hp = 7,
  getExp = function(default)
      return 6
  end,
  item = EnemyItemNone,
  type = SkillTypePhysical,
}

return Enemy