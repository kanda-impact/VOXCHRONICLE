-- 回復魔法
EnemySkill = {
  name = "HP回復",
  performSkill = function(self, user, characterManager, enemyManager)
    local layer = EffectLayer:sharedLayer()
    SimpleAudioEngine:sharedEngine():playEffect("enemy_cure.mp3")
    layer:addEffectOnEnemy(user, "enemy_cure", 3, CCRectMake(0, 0, 200, 200))
    local message = user:getName().."の　きずが　みるみるふさがっていく！"
    MessageManager:sharedManager():pushMessage(message)
    user:setHP(user:getHP() + 20)
  end
}
return EnemySkill