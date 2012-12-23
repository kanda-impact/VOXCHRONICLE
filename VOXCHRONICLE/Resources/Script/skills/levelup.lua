Skill = {
  name = "レベルアップ",
  identifier = "tension",
  power = 1,
  mp = 0,
  tensionLevel = 0,
  common = true,
  maxRepeat = 1,
  turn = 1,
  performSkill = function(self, target, characterManager, enemyManager)
    characterManager:setLevel(characterManager:getLevel() + 1)
  end,
  skillRange = SkillRangeSelf,
  skillType = SkillTypeNone
}
