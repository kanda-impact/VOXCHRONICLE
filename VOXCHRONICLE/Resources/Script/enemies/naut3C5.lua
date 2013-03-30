Enemy = {
  species = "naut",
  level = 10,
  hp = 36,
  getExp = function(default)
      return 20
  end,
  item = EnemyItemShield,
  type = SkillTypePhysical,
}

return Enemy