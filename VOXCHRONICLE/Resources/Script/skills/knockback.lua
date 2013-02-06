Skill = {
  name = "ノックバック",
  identifier = "knockback",
  power = 0,
  mp = 0,
  se = true,
  tensionLevel = 0,
  common = false,
  maxRepeat = 1,
  turn = 1,
  performSkill = function(self, target, characterManager, enemyManager)
    row = target:getRow()
    target:setRow(row + 2)
    manager = MessageManager:sharedManager()
    manager:pushMessage("オクスはノックバックを放った！")
  end,
  skillRange = SkillRangeSingle,
  skillType = SkillTypePhysical
}
