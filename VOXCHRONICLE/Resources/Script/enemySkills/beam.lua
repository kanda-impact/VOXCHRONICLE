-- ラスボス用ビーム。ノーリアクション兵器
EnemySkill = {
  name = "ビーム",
  performSkill = function(self, user, characterManager, enemyManager)
    characterManager:damage(2)
    SimpleAudioEngine:sharedEngine():playEffect("lastboss_beam.mp3")
    local layer = EffectLayer:sharedLayer()
    layer:addEffectOnEnemy(user, "enemy_skill", 3, CCRectMake(0, 0, 50, 50))
    
    local mManager = MessageManager:sharedManager()
    mManager:pushMessage(user:getName().."の　体から　閃光が　ほとばしる！")
  end
}
return EnemySkill
