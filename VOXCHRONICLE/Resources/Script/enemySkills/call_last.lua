-- 召喚技ラスボス用
EnemySkill = {
  name = "なかまをよぶ",
  performSkill = function(self, user, characterManager, enemyManager)
    -- t2phaを最前列に3体出す鬼畜
    user:setRow(MAX_ROW - 1)
    user:setCol(1)
    
    local enemy = nil
    for col = 0, 2 do
      enemy = enemyManager:popEnemyAt("t2pha3D1", 2, col)
    end
--[[      local messages = {
user:getName().."は mmm",
 "iii",
 "uuu"
}
      math.random(100)
      local message = messages[math.random(#messages)]
      mManager:pushMessage(message)
    --user:getName().."は "..enemy:getName().."を　召喚した"]]
  end
}
return EnemySkill
