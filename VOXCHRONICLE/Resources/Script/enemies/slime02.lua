Enemy = {
  species = "slime",
  level = 10,
  hp = 6,
  getExp = function(default)
      return default
  end,
  item = EnemyItemNone,
  type = SkillTypePhysical,
}

return Enemy