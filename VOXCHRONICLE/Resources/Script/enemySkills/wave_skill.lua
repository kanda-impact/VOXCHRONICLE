-- 波召喚攻撃
EnemySkill = {
  name = "津波",
  performSkill = function(self, user, characterManager, enemyManager)
    row = user:getRow()
    math.random(100)
    col = math.random(3) - 1
    SimpleAudioEngine:sharedEngine():playEffect("enemy_wave.mp3")
    --テキストのランダム化
    local text = {
      user:getName().."は　つなみを　おこした！",
      user:getName().."の　おおつなみがおそう",
      user:getName().."の　つなみ　こうげき！"
    }
    local rand = math.random(#text)
    MessageManager:sharedManager():pushMessage(text[rand])
    enemyManager:popEnemyAt("wave3C0", row, col) -- 波を1つ生成する 
  end
}
return EnemySkill