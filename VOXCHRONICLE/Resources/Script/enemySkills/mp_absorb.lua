-- MP吸収
EnemySkill = {
  name = "MP吸収",
  performSkill = function(self, user, characterManager, enemyManager)
    SimpleAudioEngine:sharedEngine():playEffect("enemy_burn.mp3")

    local layer = EffectLayer:sharedLayer()
    layer:addEffectOnEnemy(nil, "run", 3, CCRectMake(0, 0, 120, 80))

    local mManager = MessageManager:sharedManager()
    characterManager:addMP(-1 * characterManager:getMP())

    local text = {
      user:getName().."の　からだから はどうが　ほとばしる",
      user:getName().."が　ぶきみな　ちからを　つかった"
    }
    local rand = math.random(#text)
    mManager:pushMessage(text[rand])


    local text = {
      "MPが　すべて　なくなってしまった",
      "まりょくが　すべて　きえてしまった"
    }
    local rand = math.random(#text)
    mManager:pushMessage(text[rand])
    --mManager:pushMessage(characterManager:getCurrentCharacter():getName().."の　MPが　全てなくなってしまった")
    --主語禁止（オクスの時に使われて「オクスのMPがなくなってしまった」となるため）
  end
}
return EnemySkill
