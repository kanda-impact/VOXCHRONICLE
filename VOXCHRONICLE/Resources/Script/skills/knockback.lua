Skill = {
  name = "ノックバック",
  slug = "knockback",
  power = 0,
  mp = 0,
  common = false,
  maxRepeat = 1,
  turn = 1,
  performSkill = function(target)
    target:setRow(MAX_ROW - 1);
  end,
  skillRange = SkillRangeSingle,
  skillType = SkillTypePhysical
}
