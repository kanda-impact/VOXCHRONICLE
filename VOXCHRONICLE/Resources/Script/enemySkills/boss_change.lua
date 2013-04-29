-- 第2形態チェンジ
EnemySkill = {
  name = "第2形態チェンジ",
  performSkill = function(self, user, characterManager, enemyManager)
    local key = "bossChange"
    local turn = user:getRegister(key, 0)
    local mManager = MessageManager:sharedManager() -- メッセージマネージャーを取り出す
    if turn == 0 then
      user:setRegister(key, turn + 1) -- ターンを+1する
      user:setRow(1)
      user:setCol(1)
      SimpleAudioEngine:sharedEngine():playEffect("menu_cancel.mp3")
    elseif turn == 1 then
      user:setRegister(key, turn + 1) -- ターンを+1する
      -- 点滅させる処理を入れる
      local actions = CCArray:create()
      actions:addObject(CCFadeTo:create(0.05, 128))
      actions:addObject(CCFadeTo:create(0.05, 255))
      local sequence = CCSequence:create(actions)
      user:runAction(CCRepeat:create(sequence, 10))      
    elseif turn == 2 then
      SimpleAudioEngine:sharedEngine():playEffect("enemy_burn.mp3")
      
      local bitL = enemyManager:popEnemyAt("L_bit_boss", 1, 0)
      local newEnemy = enemyManager:popEnemyAt("last2_boss", 1, 1)
      local bitR = enemyManager:popEnemyAt("R_bit_boss", 1, 2)
      
      local messages ={
       user:getName().."は "..newEnemy:getName().."に　すがたをかえた！",
       user:getName().."は "..newEnemy:getName().."に　へんしんした！",
       user:getName().."のしょうたいは"..newEnemy:getName().."だった！",
       user:getName().."はしんのすがた"..newEnemy:getName().."になった！"
       }
      math.random(100)
      local message2 = messages[math.random(#messages)]
      mManager:pushMessage(message2)
      
      enemyManager:setBoss(newEnemy)
      enemyManager:removeEnemy(user)
      
      local layer = EffectLayer:sharedLayer()
      layer:addEffectOnEnemy(nil, "run", 3, CCRectMake(0, 0, 120, 80))
      user:setRegister(key, turn + 1) -- ターンを+1する
    elseif turn == 3 then
      user:setRegister(key, 0) -- 溜めターンを0にする
    end
  end
}
return EnemySkill
