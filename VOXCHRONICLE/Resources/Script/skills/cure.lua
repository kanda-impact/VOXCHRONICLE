Skill = {
  name = "ＨＰヒーリング",
  identifier = "cure",
  mp = 1,
  tensionLevel = 0,
  effectFrames = 7,
  common = false,
  cutinType = EffectLayerCutinTypeNormal,
  maxRepeat = 1,
  se = true,
  turn = 1,
  loop = true,
  canRepeat = true,
  keepTension = false,
  performSkill = function(self, target, characterManager, enemyManager)
    local tension = characterManager:getTension() -- テンションをとって
    local power = self:getPower(characterManager) -- パワーとって
    local rate = power / 10.0 -- 割合出して
    local max = characterManager:getMaxHP() -- 最大値出して
    local cure = math.ceil(max * rate)
    characterManager:addHP(cure) -- 回復させる
    EffectLayer:sharedLayer():addDamageLabel(-cure, 0, DamageLabelTypeCure)
  end,
  getPower = function(characterManager)
    local tension = characterManager:getTension()
    t = {2, 3, 4, 5, 6}
    return t[tension + 1]
  end,
  skillRange = SkillRangeSelf,
  skillType = SkillTypeNone,
  --回復成功時
  messages = {
    "きずが　かいふくした",
    "みるみる　きずが　ふさがっていく",
    "たいりょくが　かいふくした",
    "かつりょくが　みなぎる",
    "つかれが　ふきとんだ",
    "いたいの　いたいの　とんでいけー",
    "からだの　いたみが　きえていく"
  },
  getMessageTable = function(map, characterManager, enemyManager)
    return {}
  end,
   --すでに満タンだった場合
    messages = {
    "そもそも　からだにきずが　なかった",
    "まだだいじょうぶ　あんしんしろ",
    "おちつけ　まだだいじょうぶだ",
    "ＨＰは　さいだいち　デス",
    "すでに　きずは　ふさがっている",
    "とんでいく　いたみが　なかった",
  }
}
