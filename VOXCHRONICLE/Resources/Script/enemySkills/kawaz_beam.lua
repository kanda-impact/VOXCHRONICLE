-- かわずたん用ビーム。ノーリアクション兵器
EnemySkill = {
  name = "ビーム",
  performSkill = function(self, user, characterManager, enemyManager)
    SimpleAudioEngine:sharedEngine():playEffect("lastboss_beam.mp3")
    local layer = EffectLayer:sharedLayer()
    layer:addEffectOnEnemy(user, "enemy_skill", 3, CCRectMake(0, 0, 200, 200))
    
    local mManager = MessageManager:sharedManager()
    local text ={user:getName().."の　杖から　閃光が　ほとばしる！",
                 user:getName().."は　剣を　高く　かかげた！",
                 user:getName().."の　杖から　閃光が　ほとばしる！"
                 }
    local rand = math.random(3)
    characterManager:damage(1)
    mManager:pushMessage(text[rand])
  end
}
return EnemySkill
