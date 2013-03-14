Enemy = {
  species = "L_strfoot",
  level = 1,
  hp = 50,
  getExp = function(default)
      return 0
  end,
  item = EnemyItemMagical,
  type = SkillTypeNormal,
}

return Enemy