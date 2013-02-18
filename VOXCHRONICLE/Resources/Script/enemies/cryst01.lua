Enemy = {
  species = "cryst",
  level = 25,
  hp = 10,
  getExp = function(default)
      return default
  end,
  item = EnemyItemBarrier,
  type = SkillTypeNormal,
}

return Enemy