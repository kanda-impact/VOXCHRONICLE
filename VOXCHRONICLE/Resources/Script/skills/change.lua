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
  keepTension = false,
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
  getMessageTable = function(self, targets, map, characterManager, enemyManager)
    if characterManager:getCurrentCharacter():getCharacterType() == CharacterTypeVox then
      return { -- オクス→ラスカ
        "シャバデゥビ　タッチ　コウターイ！",
        "チェンジ！",
        "たのんだぜ　ラスカ",
        "まかせたぞ　ラスカ",
        "たのむ　ラスカ！"
      } 
    else
      return { -- ラスカ→オクス
        "ちぇーーんじ",
        "まかせるわ　オクス",
        "たのむわよ　オクス",
        "いっけー　オクス"
      }
    end
    return {}
  end
}
