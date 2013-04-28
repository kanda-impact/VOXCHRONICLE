Skill = {
  name = "チェンジ",
  identifier = "change",
  effectFrames = 0,
  mp = 0,
  se = true,
  tensionLevel = 0,
  common = false,
  canRepeat = true,
  cutinType = EffectLayerCutinTypeNormal,
  maxRepeat = 1,
  turn = 1,
  loop = true,
  performSkill = function(self, target, characterManager, enemyManager)
    characterManager:changeCharacter()
  end,
  getPower = function(characterManager)
    return 0
  end,
  skillRange = SkillRangeSelf,
  skillType = SkillTypeNone,
--オクスからラスカへ
messages = {
    "シャバデゥビ　タッチ　コウターイ！",
    "チェンジ！",
    "たのんだぜ　ラスカ",
    "まかせたぞ　ラスカ",
    "たのむ　ラスカ！"
    },
--ラスカからオクスへ
  messages = {
    "ちぇーーんじ",
    "まかせるわ　オクス",
    "たのむわよ　オクス",
    "いっけー　オクス"
    }
}
