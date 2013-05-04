Skill = {
  name = "ノックバック",
  identifier = "knockback",
  effectFrames = 3,
  mp = 0,
  se = true,
  tensionLevel = 0,
  common = false,
  cutinType = EffectLayerCutinTypeNormal,
  maxRepeat = 1,
  turn = 1,
  loop = true,
  canRepeat = true,
  keepTension = false,
  performSkill = function(self, target, characterManager, enemyManager)
    row = target:getRow()
    local newRow = row + 4
    if newRow >= MAX_ROW then
      newRow = MAX_ROW - 1
    end
    target:setRow(newRow)
  end,
  getPower = function(characterManager)
    local tension = characterManager:getTension()
    t = {0, 2, 4, 8, 16}
    return t[tension + 1]
  end,
  skillRange = SkillRangeSingle,
  skillType = SkillTypePhysical,
  getMessageTable = function(self, targets, map, characterManager, enemyManager)
    if targets:count() == 1 then
      local target = targets:objectAtIndex(0)
      if not target:getSpecies():isEnableSkill(self) then
        return { -- 失敗時
          "モンスターは　びくともしない",
          "こうかは　なかったようだ",
          "てきがおもすぎて　ふきとばない",
          "ふきとばしのちからが　はじかれてしまった"
        }
      end
    end
    return { -- 成功時
      "モンスターを　はじきとばした",
      "とっぷうが　てきを　ふきとばした",
      "たつまきが　てきを　うしろへおいやる",
      "ふきとばしの　こうかが　はつどうした",
      "ふしぎなちからで　てきがふきとんだ"
    }
  end
}
