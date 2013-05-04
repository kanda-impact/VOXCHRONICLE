-- 蘇生魔法
EnemySkill = {
  name = "蘇生魔法",
  performSkill = function(self, user, characterManager, enemyManager)
    local mManager = MessageManager:sharedManager() -- メッセージマネージャーを取り出す
    local layer = EffectLayer:sharedLayer()
      
    SimpleAudioEngine:sharedEngine():playEffect("enemy_revive.mp3")
    local isRightExist = false
    local isLeftExist = false
    
    local layer = EffectLayer:sharedLayer()
    
    local enemies = enemyManager:getEnemies()
    local count = enemies:count()
    for i=0, count - 1 do
      local enemy = enemies:objectAtIndex(i)
      if enemy:getIdentifier() == "R_strclaw3C0" then
        isRightExist = true
      elseif enemy:getIdentifier() == "L_strclaw3C0" then
        isLeftExist = true
      end
    end
    
    if not isRightExist then
      local foot = enemyManager:popEnemyAt("R_strclaw3C0", 2, 2)
      local maxHP = foot:getMaxHP()
      layer:addDamageLabelOnEnemy(foot, maxHP, DamageLabelTypeCure)
      layer:addEffectOnEnemy(foot, "enemy_cure", 3, CCRectMake(0, 0, 100, 100))
    end
    
    if not isLeftExist then
      local foot = enemyManager:popEnemyAt("L_strclaw3C0", 2, 0)
      local maxHP = foot:getMaxHP()
      layer:addDamageLabelOnEnemy(foot, maxHP, DamageLabelTypeCure)
      layer:addEffectOnEnemy(foot, "enemy_cure", 3, CCRectMake(0, 0, 100, 100))
    end
  
    local message = "なんと　"..user:getName().."の　足が　再生した！"
    MessageManager:sharedManager():pushMessage(message)
  end
}
return EnemySkill