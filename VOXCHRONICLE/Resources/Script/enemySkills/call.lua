-- 召喚技
EnemySkill = {
  name = "なかまをよぶ",
  performSkill = function(self, user, characterManager, enemyManager)
    local species = user:getIdentifier()
    local row = user:getRow()
    local col = user:getCol()
    local newCol = (col + math.random(0, 1)) % 3
    local enemy = enemyManager:popEnemyAt(species, row, newCol)
    local mManager = MessageManager:shaderManager()
    local text = {
      user:getName().."は　なかまを　よんだ",
      user:getName().."は　なかまを　ふやした",
      user:getName().."は　えんぐんを　よんだ",
      user:getName().."は　たすけを　よんだ",
      user:getName().."が　まものを　ふやした"
    }
    local rand = math.random(#text)
    mManager:pushMessage(text[rand])


    local text = {
      enemy:getName().."が　あらわれた！",
      enemy:getName().."が　しゅつげん！",
      enemy:getName().."が　うみだされた！"
    }
    local rand = math.random(#text)
    mManager:pushMessage(text[rand])
  end
}
return EnemySkill
