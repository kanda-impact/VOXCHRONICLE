Skill = {
  name = "ノックバック",
  identifier = "knockback",
  effectFrames = 0,
  mp = 0,
  se = true,
  tensionLevel = 0,
  common = false,
  maxRepeat = 1,
  turn = 1,
  performSkill = function(self, target, characterManager, enemyManager)
    row = target:getRow()
    local newRow = row + 2
    if newRow >= MAX_ROW then
      newRow = MAX_ROW - 1
    end
    target:setRow(newRow)
  end,
  getPower = function(tension)
    t = {0, 2, 4, 6, 9}
    return t[tension + 1]
  end,
  skillRange = SkillRangeSingle,
  skillType = SkillTypePhysical,
  messages = {
    ""
  }
}
