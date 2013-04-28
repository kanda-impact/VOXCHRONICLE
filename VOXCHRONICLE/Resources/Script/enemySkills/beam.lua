-- ラスボス用ビーム。ノーリアクション兵器
EnemySkill = {
  name = "ビーム",
  performSkill = function(self, user, characterManager, enemyManager)
    characterManager:damage(2)
    SimpleAudioEngine:sharedEngine():playEffect("lastboss_beam.mp3")
    local layer = EffectLayer:sharedLayer()
    layer:addEffectOnEnemy(user, "enemy_skill", 3, CCRectMake(0, 0, 50, 50))
    
    local mManager = MessageManager:sharedManager()
      local messages = {
      user:getName().."の　からだから　せんこうが　ほとばしる！", 
      user:getName().."の　レーザー　こうげき！！", 
      user:getName().."から　エネルギーこうせんが！",
      }
      math.random(100)
      local message = messages[math.random(#messages)]
    mManager:pushMessage(message)
  end
}
return EnemySkill