Enemy = {
  species = "L_plclaw",
  level = 1,
  hp = 24,
  getExp = function(default)
      return 6
  end,
  attack = 1,
  item = EnemyItemNone,
  type = SkillTypePhysical,
}

return Enemy