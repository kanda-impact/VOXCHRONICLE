Skill = {
  name = "ノックバック",
  identifier = "knockback",
  mp = 0,
  se = true,
  tensionLevel = 0,
  common = false,
  maxRepeat = 1,
  turn = 1,
  performSkill = function(self, target, characterManager, enemyManager)
    row = target:getRow()
    target:setRow(row + 2)
  end,
  getPower = function(tension)
    t = {0, 1, 2, 3, 5}
    return t[tension + 1]
  end,
  skillRange = SkillRangeSingle,
  skillType = SkillTypePhysical,
  messages = {
    ""
  }
}
