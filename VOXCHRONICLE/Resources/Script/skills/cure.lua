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
  getMessageTable = function(self, targets, map, characterManager, enemyManager)
    local hp = characterManager:getHP()
    local maxHP = characterManager:getMaxHP()
    if hp == maxHP then
      return { -- 元からHP最大だったとき
        "そもそも　からだにきずが　なかった",
        "まだだいじょうぶ　あんしんしろ",
        "おちつけ　まだだいじょうぶだ",
        "ＨＰは　さいだいち　デス",
        "すでに　きずは　ふさがっている",
        "とんでいく　いたみが　なかった",
      }
    end
    return {
      "きずが　かいふくした",
      "みるみる　きずが　ふさがっていく",
      "たいりょくが　かいふくした",
      "かつりょくが　みなぎる",
      "つかれが　ふきとんだ",
      "いたいの　いたいの　とんでいけー",
      "からだの　いたみが　きえていく"
    }
  end,
}
