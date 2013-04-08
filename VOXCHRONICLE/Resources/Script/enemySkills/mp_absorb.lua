-- MP吸収
EnemySkill = {
  name = "MP吸収",
  performSkill = function(self, user, characterManager, enemyManager)
    SimpleAudioEngine:sharedEngine():playEffect("enemy_burn.mp3")
    
    local layer = EffectLayer:sharedLayer()
    layer:addEffectOnEnemy(nil, "run", 3, CCRectMake(0, 0, 480, 320))
    
    local mManager = MessageManager:shaderManager()
    characterManager:addMP(-characterManager:getMP())
    mManager:pushMessage(user:getName().."の　全身から 波動が　ほとばしる")
    mManager:pushMessage(user:getName().."の MPが　全てなくなってしまった")
  end
}
return EnemySkill
