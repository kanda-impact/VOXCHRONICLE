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
  
    --ノックバックが成功した時
    local voxMessages = {
      "シャバデゥビ　タッチ　コウターイ！",
      "チェンジ！",
      "たのんだぜ　ラスカ",
      "まかせたぞ　ラスカ",
      "たのむ　ラスカ！"
    }
    
    --ノックバック耐性で敵が吹き飛ばせなかった時
    local lskMessages = {
      "ちぇーーんじ",
      "まかせるわ　オクス",
      "たのむわよ　オクス",
      "いっけー　オクス"
    }
    
    local messages = {}
    if characterManager:getCurrentCharacter():getCharacterType() == CharacterTypeVox then
      messages = voxMessages
    else
      messages = lskMessages
    end
    math.random(100)
    local messageManager = MessageManager:sharedManager()
    messageManager:pushMessage(messages[math.random(#messages)])
    
    characterManager:changeCharacter()
      
  end,
  getPower = function(characterManager)
    return 0
  end,
  skillRange = SkillRangeSelf,
  skillType = SkillTypeNone,
  messages = {}
}