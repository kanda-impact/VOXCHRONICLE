Enemy = {
  species = "cryst",
  level = 10,
  hp = 18,
  getExp = function(default)
      return 15
  end,
  item = EnemyItemShield,
  type = SkillTypePhysical,
}

return Enemy