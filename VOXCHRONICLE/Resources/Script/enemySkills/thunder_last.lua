-- のろい
EnemySkill = {
  name = "のろいのことば",
  performSkill = function(self, user, characterManager, enemyManager)
    SimpleAudioEngine:sharedEngine():playEffect("enemy_burn.mp3")

    local layer = EffectLayer:sharedLayer()

    local mManager = MessageManager:sharedManager()
    local key = "skill_last"
    local turn = user:getRegister(key,0)
    if turn <= 1 then
      -- 溜め初回ターンの時
      user:setAnimationClip("attack", 1, true) -- グラを変更する
      mManager:pushMessage(user:getName().."は　やみのまほうを　となえている")
      user:setRegister(key, turn + 1)
      user:setRow(2)
    elseif turn >= 2 then
      layer:addEffectOnEnemy(nil, "thunder", 6, CCRectMake(0, 0, 120, 80)):setColor(ccc3(230, 0, 138))
      if not characterManager:getShield()  then
      characterManager:addMP(-1)
      end
      characterManager:damage(8)
      user:setDefaultAnimationClip() -- グラを元に戻す
      mManager:pushMessage("やみのいなずまが　"..characterManager:getCurrentCharacter():getName().."を　つらぬく！")
      user:setRegister(key, 0)
      user:setRow(1)
      print("hoge!")
    end
  end
}
return EnemySkill
