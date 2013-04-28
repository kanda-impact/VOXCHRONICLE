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
      mManager:pushMessage(user:getName().."は　のろいのことばを　くちにしている")
      user:setRegister(key, 1)
    elseif turn == 1 then
      layer:addEffectOnEnemy(nil, "thunder", 3, CCRectMake(0, 0, 120, 80))
      if not characterManager:getShield()  then
      characterManager:addMP(-1)
      end
      characterManager:damage(8)
      mManager:pushMessage(characterManager:getCurrentCharacter():getName().."の　こころに きずがついた")
      user:setRegister(key, 0)
    end
  end
}
return EnemySkill
