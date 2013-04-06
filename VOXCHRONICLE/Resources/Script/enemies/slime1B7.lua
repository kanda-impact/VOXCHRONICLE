Enemy = {
  species = "slime",
  level = 10,
  hp = 6,
  getExp = function(default)
      return 24
  end,
  item = EnemyItemBarrier,
  type = SkillTypePhysical,
}

return Enemy