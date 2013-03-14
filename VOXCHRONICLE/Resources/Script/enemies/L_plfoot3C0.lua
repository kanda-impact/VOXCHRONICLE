Enemy = {
  species = "L_plfoot",
  level = 1,
  hp = 60,
  getExp = function(default)
      return 0
  end,
  item = EnemyItemPhysical,
  type = SkillTypeNormal,
}

return Enemy