-- 回復魔法
EnemySkill = {
  name = "HP回復",
  performSkill = function(self, user, characterManager, enemyManager)
    local cure = 15
    local layer = EffectLayer:sharedLayer()
    for i=0, enemyManager:getEnemies():count() - 1 do
      local target = enemyManager:getEnemies():objectAtIndex(i)
      SEManager:sharedManager():registerEffect("enemy_cure.mp3", 0.1)
      layer:addEffectOnEnemy(user, "enemy_skill", 3, CCRectMake(0, 0, 200, 200))
      layer:addEffectOnEnemy(target, "enemy_cure", 3, CCRectMake(0, 0, 200, 200))
      layer:addDamageLabelOnEnemy(target, cure, DamageLabelTypeCure)
      user:setHP(user:getHP() + cure)  
    end
    local message = user:getName().."たちの　きずが　みるみるふさがっていく！"
    MessageManager:sharedManager():pushMessage(message)
  end
}
return EnemySkill