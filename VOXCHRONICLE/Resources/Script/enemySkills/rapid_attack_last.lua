-- のろい
EnemySkill = {
  name = "のろいのことば",
  performSkill = function(self, user, characterManager, enemyManager)
    SimpleAudioEngine:sharedEngine():playEffect("enemy_burn.mp3")

    local layer = EffectLayer:sharedLayer()

    local mManager = MessageManager:sharedManager()
    local key = "skill_last"
    local turn = user:getRegister(key,0)
    if turn == 0 then
      -- 溜め初回ターンの時
      user:setAnimationClip("attack", 1, true) -- グラを変更する
      mManager:pushMessage(user:getName().."は　ふかく　こしを　おとした")
      user:setRegister(key, turn + 1)
      user:setRegister("skillType", 1)
      user:setRow(0)
    elseif turn >= 2 then
      layer:addEffectOnEnemy(nil, "knockback", 3, CCRectMake(0, 0, 50, 50)):setColor(ccc3(230, 0, 138))
      for i = 0 ,3 ,1 do
      local rand = math.random(6)
      characterManager:damage(rand)
      end
      user:setDefaultAnimationClip() -- グラを元に戻す
      mManager:pushMessage(user:getName().."の　こぶしが　"..characterManager:getCurrentCharacter():getName().."に　おそいかかる！")
      user:setRegister(key, 0)
      user:setRow(1)
    else
      user:setRegister(key, turn + 1)
    end
  end
}
return EnemySkill
