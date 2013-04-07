-- 回復魔法
EnemySkill = {
  name = "HP回復",
  performSkill = function(self, user, characterManager, enemyManager)
    row = user:getRow()
    math.random(100)
    col = math.random(3)
    local layer = EffectLayer:sharedLayer()
    SimpleAudioEngine:sharedEngine():playEffect("enemy_cure.mp3")
    layer:addEffectOnEnemy(user, "enemy_cure", 3, CCRectMake(0, 0, 200, 200))
    local message = user:getName().."の　きずが　みるみるふさがっていく！"
    mManager:pushMessage(message)
    user:setHP(10)
  end
}
return EnemySkill