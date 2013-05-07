-- 回復魔法
EnemySkill = {
  name = "HP回復",
  performSkill = function(self, user, characterManager, enemyManager)
    local cure = 15
    local layer = EffectLayer:sharedLayer()
    for i=0, enemyManager:getEnemies():count() - 1 do
      local target = enemyManager:getEnemies():objectAtIndex(i)
      target = tolua.cast(target, "Enemy")
      SEManager:sharedManager():registerEffect("enemy_cure.mp3", 0.1)
      layer:addEffectOnEnemy(user, "enemy_skill", 3, CCRectMake(0, 0, 50, 50))
      layer:addEffectOnEnemy(target, "enemy_cure", 3, CCRectMake(0, 0, 50, 50))
      layer:addDamageLabelOnEnemy(target, cure, DamageLabelTypeCure)
      target:setHP(target:getHP() + cure)
    end

    local mManager = MessageManager:sharedManager()

    local text = {
      user:getName().."たちの　きずが　みるみるふさがっていく！",
      user:getName().."たちの　たいりょくが　かいふくした！",
      user:getName().."たちが　げんき　ぴんぴんに　なった！"
    }
    local rand = math.random(#text)
    mManager:pushMessage(text[rand])

  end
}
return EnemySkill