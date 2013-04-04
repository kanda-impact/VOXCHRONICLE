Enemy = {
  species = "wave",
  level = 10,
  hp = 350,
  getExp = function(default)
      return 0
  end,
  item = EnemyItemNone,
  type = SkillTypeNormal,
}

return Enemy