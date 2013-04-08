-- 召喚技ラスボス用
EnemySkill = {
  name = "なかまをよぶ",
  performSkill = function(self, user, characterManager, enemyManager)
    -- t2phaを最前列に3体出す鬼畜
    local enemy = nil
    for col = 0, 2 do
      enemy = enemyManager:popEnemyAt("t2pha3D1", 2, col)
    end
    local mManager = MessageManager:sharedManager()
    mManager:pushMessage(user:getName().."は "..enemy:getName().."を　召喚した")
  end
}
return EnemySkill
