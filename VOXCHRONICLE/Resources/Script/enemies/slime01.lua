Enemy = {
  species = "slime",
  level = 7,
  hp = 6,
  getExp = function(default)
      return default
  end,
  item = EnemyItemNone,
  type = SkillTypePhysical,
}

return Enemy