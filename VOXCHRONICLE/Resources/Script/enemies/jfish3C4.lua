Enemy = {
  species = "jfish",
  level = 10,
  hp = 28,
  getExp = function(default)
      return 14
  end,
  item = EnemyItemShield,
  type = SkillTypePhysical,
}

return Enemy