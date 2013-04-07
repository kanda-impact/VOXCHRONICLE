-- 波召喚攻撃
EnemySkill = {
  name = "津波",
  performSkill = function(self, user, characterManager, enemyManager)
    row = user:getRow()
    math.random(100)
    col = math.random(3)
    SimpleAudioEngine:sharedEngine():playEffect("enemy_wave.mp3")
    MessageManager:sharedManager():pushMessage(user:getName().."は　つなみを　おこした！")
    enemyManager:popEnemyAt("wave3C0", row, col) -- 波を3つ生成する 
  end
}
return EnemySkill