-- 回復魔法
EnemySkill = {
  name = "HP回復",
  performSkill = function(self, user, characterManager, enemyManager)
    local cure = 20
    local layer = EffectLayer:sharedLayer()
    SimpleAudioEngine:sharedEngine():playEffect("enemy_cure.mp3")
    layer:addEffectOnEnemy(user, "enemy_cure", 3, CCRectMake(0, 0, 50, 50))
    local message = user:getName().."の　きずが　みるみるふさがっていく！"
    layer:addDamageLabelOnEnemy(user, cure, DamageLabelTypeCure)
    MessageManager:sharedManager():pushMessage(message)
    user:setHP(user:getHP() + cure)
  end
}
return EnemySkill