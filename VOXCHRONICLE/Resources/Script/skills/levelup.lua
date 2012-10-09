Skill = {
  name = "レベルアップ",
  slug = "tension",
  power = 1,
  mp = 0,
  common = true,
  maxRepeat = 1,
  turn = 1,
  performSkill = function(target, characterManager)
    characterManager:setLevel(characterManager:getLevel() + 1)
  end,
  skillRange = SkillRangeSelf,
  skillType = SkillTypeNone
}
