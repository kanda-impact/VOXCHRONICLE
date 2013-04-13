Enemy = {
  species = "slime",
  level = 10,
  hp = 24,
  getExp = function(default)
      return 24
  end,
  item = EnemyItemBarrier,
  type = SkillTypePhysical,
}

return Enemy