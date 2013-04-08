-- ラスボス用ビーム。ノーリアクション兵器
EnemySkill = {
  name = "ビーム",
  performSkill = function(self, user, characterManager, enemyManager)
    characterManager:damage(2)
    SimpleAudioEngine:sharedEngine():playEffect("lastboss_beam.mp3")
    local mManager = MessageManager:shaderManager()
    mManager:pushMessage(user:getName().."の　体から　閃光が　ほとばしる！")
  end
}
return EnemySkill
