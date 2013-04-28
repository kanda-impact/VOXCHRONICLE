-- 蘇生魔法
EnemySkill = {
  name = "蘇生魔法",
  performSkill = function(self, user, characterManager, enemyManager)
    local key = "reviveTurn"
    local turn = user:getRegister(key, 0)
    local mManager = MessageManager:sharedManager() -- メッセージマネージャーを取り出す
    local layer = EffectLayer:sharedLayer()
      
    if turn == 0 then
      local message = user:getName().."は　ふっかつじゅもんを　唱えた！"
      mManager:pushMessage(message)
      user:setRegister(key, 1)
      layer:addEffectOnEnemy(user, "enemy_skill", 3, CCRectMake(0, 0, 100, 100))
    elseif turn == 1 then
      SimpleAudioEngine:sharedEngine():playEffect("enemy_revive.mp3")
      
      local target = enemyManager:popEnemyAt("L_bit_boss", 1, 0)
      local maxHP = target:getMaxHP()
      
      target:setHP(maxHP * 0.5)
      layer:addDamageLabelOnEnemy(target, maxHP * 0.5, DamageLabelTypeCure)
      
      layer:addEffectOnEnemy(target, "enemy_cure", 3, CCRectMake(0, 0, 100, 100))
    
      local message = "なんと"..target:getName().."は　いきかえった！"
      MessageManager:sharedManager():pushMessage(message)
      user:setRegister(key, 0) -- 溜めターンを0にする
    end
    
  end
}
return EnemySkill