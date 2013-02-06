Skill = {
  name = "チャージ",
  identifier = "charge",
  power = 0,
  mp = 0,
  tensionLevel = 0,
  common = false,
  maxRepeat = 1,
  se = true,
  turn = 1,
  performSkill = function(self, target, characterManager, enemyManager)
    characterManager:addMP(1)
  end,
  skillRange = SkillRangeSelf,
  skillType = SkillTypeNone,
  messages = {
    ""
  }
}
