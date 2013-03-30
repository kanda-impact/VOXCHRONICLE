Enemy = {
  species = "whale",
  level = 10,
  hp = 42,
  getExp = function(default)
      return 24
  end,
  item = EnemyItemBarrier,
  type = SkillTypeMagical,
}

return Enemy