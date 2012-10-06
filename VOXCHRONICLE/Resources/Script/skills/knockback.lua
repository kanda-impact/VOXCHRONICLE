Skill = {
  name = "ノックバック",
  slug = "knockback",
  power = 0,
  mp = 0,
  common = false,
  maxRepeat = 1,
  turn = 1,
  performSkill = function(target)
    print("hoge", target:getRow())
  end,
  skillRange = SkillRangeSingle,
  skillType = SkillTypePhysical
}
