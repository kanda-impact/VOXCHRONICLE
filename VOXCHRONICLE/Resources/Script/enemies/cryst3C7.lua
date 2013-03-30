Enemy = {
  species = "cryst",
  level = 10,
  hp = 18,
  getExp = function(default)
      return 15
  end,
  item = EnemyItemPhysical,
  type = SkillTypeMagical,
}

return Enemy