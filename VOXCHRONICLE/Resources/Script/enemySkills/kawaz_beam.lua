-- かわずたん用ビーム。ノーリアクション兵器
EnemySkill = {
  name = "ビーム",
  performSkill = function(self, user, characterManager, enemyManager)
    SimpleAudioEngine:sharedEngine():playEffect("lastboss_beam.mp3")
    local layer = EffectLayer:sharedLayer()
    layer:addEffectOnEnemy(user, "enemy_skill", 3, CCRectMake(0, 0, 50, 50))
    local mManager = MessageManager:sharedManager()
    local text ={user:getName().."の　杖から　閃光が　ほとばしる！",
      user:getName().."は　剣を　高く　かかげた！",
      user:getName().."の　杖から　閃光が　ほとばしる！"
    }
    local rand = math.random(3)
    if user:getType() == SkillTypePhysical then
      characterManager:damage(2)
    else
      characterManager:damage(1)
    end
    mManager:pushMessage(text[rand])
  end
}
return EnemySkill
