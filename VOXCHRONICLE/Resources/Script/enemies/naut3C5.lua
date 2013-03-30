Enemy = {
  species = "naut",
  level = 10,
  hp = 36,
  getExp = function(default)
      return 20
  end,
  item = EnemyItemBarrier,
  type = SkillTypeNormal,
}

return Enemy