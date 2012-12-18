Skill = {
  name = "チャージ",
  slug = "charge",
  power = 0,
  mp = 0,
  tensionLevel = 0,
  common = false,
  maxRepeat = 1,
  turn = 1,
  performSkill = function(target, characterManager)
    characterManager:addMP(1)
  end,
  skillRange = SkillRangeSelf,
  skillType = SkillTypeNone
}
