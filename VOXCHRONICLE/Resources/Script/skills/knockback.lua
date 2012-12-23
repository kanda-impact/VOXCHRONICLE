Skill = {
  name = "ノックバック",
  identifier = "knockback",
  power = 0,
  mp = 0,
  tensionLevel = 0,
  common = false,
  maxRepeat = 1,
  turn = 1,
  performSkill = function(self, target, characterManager, enemyManager)
    target:setRow(MAX_ROW - 1)
  end,
  skillRange = SkillRangeSingle,
  skillType = SkillTypePhysical
}
