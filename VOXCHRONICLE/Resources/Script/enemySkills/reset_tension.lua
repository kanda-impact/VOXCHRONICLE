-- いてつくはどう
EnemySkill = {
  name = "いてつくはどう",
  performSkill = function(self, user, characterManager, enemyManager)
    local key = "tensionWave"
    local turn = user:getRegister(key, 0)
    local mManager = MessageManager:sharedManager() -- メッセージマネージャーを取り出す
    if turn == 0 then
      local message = user:getName().."の　ゆびさきから　はどうが　ほとばしる"
      mManager:pushMessage(message)
      user:setRegister(key, 1)
    elseif turn == 1 then
      SimpleAudioEngine:sharedEngine():playEffect("enemy_burn.mp3")
      local message2 = characterManager:getCurrentCharacter():getName().."の　テンションが　もとにもどってしまった！"
      mManager:pushMessage(message2)
      local layer = EffectLayer:sharedLayer()
      layer:addEffectOnEnemy(nil, "run", 3, CCRectMake(0, 0, 480, 320))
      characterManager:setRepeatCount(0)
      characterManager:resetTension() -- テンションを0にする
      user:setRegister(key, 0) -- 溜めターンを0にする
    end
  end
}
return EnemySkill
