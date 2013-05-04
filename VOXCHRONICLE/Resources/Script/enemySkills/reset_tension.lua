-- いてつくはどう
EnemySkill = {
  name = "いてつくはどう",
  performSkill = function(self, user, characterManager, enemyManager)
    local key = "tensionWave"
    local turn = user:getRegister(key, 0)
    local mManager = MessageManager:sharedManager() -- メッセージマネージャーを取り出す
    if turn == 0 then
        local text = {
          user:getName().."の　めから　はどうが　ほとばしる",
          user:getName().."の　オーラが　ふくれあがる"
        }
        local rand = math.random(#text)
        mManager:pushMessage(text[rand])
      user:setRegister(key, 1)
    elseif turn == 1 then
      SimpleAudioEngine:sharedEngine():playEffect("enemy_burn.mp3")
        local text = {
          user:getName().."の　めから　はどうが　ほとばしる",
          user:getName().."の　オーラが　ふくれあがる",
          characterManager:getCurrentCharacter():getName().."の　パワーが　もとにもどってしまった！",
          characterManager:getCurrentCharacter():getName().."の　やるきが　おもいきりなえた！"
        }
        local rand = math.random(#text)
        mManager:pushMessage(text[rand])

      local layer = EffectLayer:sharedLayer()
      layer:addEffectOnEnemy(nil, "run", 3, CCRectMake(0, 0, 120, 80))
      characterManager:setRepeatCount(0)
      characterManager:resetTension() -- テンションを0にする
      user:setRegister(key, 0) -- 溜めターンを0にする
    end
  end
}
return EnemySkill
