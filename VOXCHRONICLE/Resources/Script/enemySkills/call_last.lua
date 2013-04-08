-- 召喚技ラスボス用
EnemySkill = {
  name = "なかまをよぶ",
  performSkill = function(self, user, characterManager, enemyManager)
    -- t2phaを最前列に3体出す鬼畜
    local enemyName = "t2pha3D1"
    local enemy = nil
    for col = 0, 3 do
      enemy = enemyManager:popEnemyAt(ememyName, 0, col)
    end
    local mManager = MessageManager:shaderManager()
    mManager:pushMessage(user:getName().."は "..enemy:getName().."を　召喚した")
  end
}
return EnemySkill
