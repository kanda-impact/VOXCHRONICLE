Skill = {
  name = "マジック",
  identifier = "magic",
  effectFrames = 6,
  mp = 0,
  se = false,
  tensionLevel = 0,
  common = false,
  cutinType = EffectLayerCutinTypeNormal,
  maxRepeat = 4,
  turn = 1,
  loop = true,
  canRepeat = true,
  keepTension = false,
  performSkill = function(self, target, characterManager, enemyManager)
    local hit = true
    if target:getItem() == EnemyItemBarrier then
      hit = false
    elseif target:getType() == SkillTypeMagical then
      local power = self:getPower(characterManager)
      if target:getHP() > math.ceil(power / 2.0) then
        hit = false
      end
    end
    
    if hit then

      local basename = "magic_effect"
      local number = characterManager:getRepeatCount()
      local ext = ".mp3"
      local filename = basename..number..ext
      SimpleAudioEngine:sharedEngine():playEffect(filename)
    end
  end,
  getPower = function(characterManager)
    local repeatCount = characterManager:getRepeatCount()
    repeatPower = {0,1,3,6}
    local tension = characterManager:getTension()
    t = {3, 9, 14, 18, 24}
    return t[tension + 1] + repeatPower[repeatCount + 1]
  end,
  skillRange = SkillRangeSingle,
  skillType = SkillTypeMagical,
  getMessageTable = function(self, targets, map, characterManager, enemyManager)
    if targets:count() > 0 then
      local target = targets:count()
      if target:getSkillType() == SkillTypeMagical or target:getItem() == EnemyItemBarrier or target:getSpecies():isEnableSkill(self) then -- 効かない相手にはメッセージ表示しない
        return {}
      end 
    end
    return {
      "ラスカの　アイスブレイク！",
      "たちふさがるものを　ひょうけつさせる！",
      "くうきが　こおりついていく",
      "こおりつけ！　モンスター！",
      "つえのさきから　れいきがほどばしる",
      "ラスカの　ブリザード　アタック"
    }
  end
}
