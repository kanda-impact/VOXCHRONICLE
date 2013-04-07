Skill = {
  name = "アタック",
  identifier = "attack",
  effectFrames = 4,
  mp = 0,
  se = false,
  tensionLevel = 0,
  common = false,
  cutinType = EffectLayerCutinTypeNormal,
  maxRepeat = 4,
  turn = 1,
  loop = true,
  skillRange = SkillRangeSingle,
  skillType = SkillTypePhysical,
  performSkill = function(self, target, characterManager, enemyManager)
    local basename = "attack_effect"
    local number = characterManager:getRepeatCount()
    local ext = ".mp3"
    local filename = basename..number..ext
    SimpleAudioEngine:sharedEngine():playEffect(filename)
  end,
  getPower = function(characterManager)
    local repeatCount = characterManager:getRepeatCount()
    repeatPower = {0,1,2,3}
    local tension = characterManager:getTension()
    t = {3, 9, 12, 15, 30}
    return t[tension + 1] +repeatPower[repeatCount + 1]
  end,
  messages = {
    ""
  }
}
