Skill = {
  name = "攻撃",
  identifier = "attack",
  effectFrames = 6,
  mp = 0,
  se = false,
  tensionLevel = 0,
  common = false,
  maxRepeat = 4,
  turn = 1,
  skillRange = SkillRangeSingle,
  skillType = SkillTypePhysical,
  performSkill = function(self, target, characterManager, enemyManager)
    local basename = "attack_effect"
    local number = math.random(0, 3)
    local ext = ".mp3"
    local filename = basename..number..ext
    SimpleAudioEngine:sharedEngine():playEffect(filename)
  end,
  getPower = function(tension)
    t = {1, 3, 5, 7, 10}
    return t[tension + 1]
  end,
  messages = {
    ""
  }
}
