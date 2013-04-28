Skill = {
  name = "アタック",
  identifier = "attack",
  effectFrames = 4,
  mp = 0,
  se = false,
  tensionLevel = 0,
  common = false,
  canRepeat = true,
  cutinType = EffectLayerCutinTypeNormal,
  maxRepeat = 4,
  turn = 1,
  loop = true,
  skillRange = SkillRangeSingle,
  skillType = SkillTypePhysical,
  performSkill = function(self, target, characterManager, enemyManager)
    local hit = true
    if target:getItem() == EnemyItemShield then
      hit = false
    elseif target:getType() == SkillTypePhysical then
      local power = self:getPower(characterManager)
      if target:getHP() > math.ceil(power / 2.0) then
        hit = false
      end
    end
    
    if hit then
      local basename = "attack_effect"
      local number = characterManager:getRepeatCount()
      local ext = ".mp3"
      local filename = basename..number..ext
      SimpleAudioEngine:sharedEngine():playEffect(filename)
    end
  end,
  getPower = function(characterManager)
    local repeatCount = characterManager:getRepeatCount()
    repeatPower = {0,1,2,3}
    local tension = characterManager:getTension()
    t = {3, 9, 12, 15, 30}
    return t[tension + 1] +repeatPower[repeatCount + 1]
  end,
  messages = {
    "オクスは　おもいきり　けんをふりおろした"
    "オクスは　けんで　こうげきした"
    "オクスの　けんが　てきをきる"
    "オクスの　こうげき！"
  }
}
